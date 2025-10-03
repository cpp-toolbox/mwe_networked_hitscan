#include <iostream>
#include <vector>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/StateRecorderImpl.h>

#include <glm/fwd.hpp>

#include "meta_program/meta_program.hpp"
#include "networking/packet_handler/packet_handler.hpp"
#include "networking/packets/packets.hpp"
#include "networking/server_networking/network.hpp"

#include "graphics/fps_camera/fps_camera.hpp"

#include "sound/sound_types/sound_types.hpp"

#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/logger/logger.hpp"
#include "utility/temporal_binary_switch/temporal_binary_switch.hpp"
#include "utility/jolt_glm_type_conversions/jolt_glm_type_conversions.hpp"
#include "utility/config_file_parser/config_file_parser.hpp"
#include "utility/meta_utils/meta_utils.hpp"

#include "system_logic/physics/physics.hpp"
#include "system_logic/random_vector/random_vector.hpp"
#include "system_logic/sphere_orbiter/sphere_orbiter.hpp"
#include "system_logic/mouse_update_logger/mouse_update_logger.hpp"
#include "system_logic/hitscan_logic/hitscan_logic.hpp"

struct CameraReconstructionData {
    double yaw;
    double pitch;
    double last_mouse_position_x;
    double last_mouse_position_y;
};

void set_camera_state(CameraReconstructionData crd, FPSCamera &fps_camera) {
    fps_camera.transform.set_rotation_yaw(crd.yaw);
    fps_camera.transform.set_rotation_pitch(crd.pitch);
    fps_camera.mouse.last_mouse_position_x = crd.last_mouse_position_x;
    fps_camera.mouse.last_mouse_position_y = crd.last_mouse_position_y;
}

int main() {

    global_logger.remove_all_sinks();
    global_logger.add_file_sink("logs.txt");

    Configuration configuration("assets/config/user_cfg.ini");

    if (configuration.get_value("general", "development_mode") == "on") {
        meta_utils::CustomTypeExtractionSettings settings("src/networking/packet_types/packet_types.hpp");
        meta_utils::CustomTypeExtractionSettings settings1("src/networking/packet_data/packet_data.hpp");
        meta_utils::CustomTypeExtractionSettings settings2("src/sound/sound_types/sound_types.hpp");
        meta_utils::CustomTypeExtractionSettings settings3("src/networking/packets/packets.hpp");
        meta_utils::register_custom_types_into_meta_types({settings, settings1, settings2, settings3});
        meta_utils::generate_string_invokers_program_wide({}, meta_utils::meta_types.get_concrete_types());
    }

    meta_program::MetaProgram mp(meta_utils::meta_types.get_concrete_types());

    bool running = true;
    unsigned int last_processed_mouse_pos_update_number = 0;

    FixedFrequencyLoop ffl;
    Physics physics;

    float room_size = 16.0f;

    SphereOrbiter sphere_orbiter(glm::vec3(0.0f, 1, 0), room_size / 2, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f),
                                 0.0f);

    auto physics_target = physics.create_character(0);

    bool subtick_firing_accuracy = true;

    FPSCamera fps_camera;

    Network network(7777);
    network.logger.disable_all_levels();
    network.initialize_network();

    MouseUpdateLogger mouse_update_logger;
    // mouse_update_logger.logger.disable_all_levels();

    PacketHandler packet_handler;

    TemporalBinarySwitch fire_tbs;

    std::vector<SoundUpdate> sound_updates_this_tick;
    std::vector<MouseUpdate> mouse_updates_since_last_tick;

    std::function<void(std::vector<uint8_t>)> mouse_update_handler = [&](std::vector<uint8_t> raw_packet) {
        LogSection _(global_logger, "mouse update handler");
        const MouseUpdatePacket packet = mp.deserialize_MouseUpdatePacket(raw_packet);
        MouseUpdate just_received_mouse_update = packet.mouse_update;
        global_logger.info("just received mouse update packet: {}", mp.MouseUpdatePacket_to_string(packet));
        mouse_updates_since_last_tick.push_back(just_received_mouse_update);
    };

    packet_handler.register_handler(PacketType::MOUSE_UPDATE, mouse_update_handler);

    unsigned int update_number = 0;
    // NOTE: the below two things are used for going back in time to take the corrected shot.
    std::unordered_map<unsigned int, JPH::StateRecorderImpl> update_number_to_physics_state;

    std::unordered_map<unsigned int, CameraReconstructionData> update_number_to_camera_reconstruction_data;

    std::function<void(double)> tick = [&](double dt) {
        LogSection _(global_logger, "tick");
        std::vector<PacketWithSize> pws = network.get_network_events_since_last_tick();
        packet_handler.handle_packets(pws);

        auto new_pos = sphere_orbiter.process(dt);
        physics_target->SetPosition(g2j(new_pos));

        // NOTE: this probably shouldn't be here in regular logic, only happening here
        // because we know that the position only changes when a new update comes in which
        JPH::StateRecorderImpl physics_target_physics_state;
        physics_target->SaveState(physics_target_physics_state);

        update_number_to_physics_state.emplace(update_number, std::move(physics_target_physics_state));

        CameraReconstructionData crd(fps_camera.transform.get_rotation_yaw(), fps_camera.transform.get_rotation_pitch(),
                                     fps_camera.mouse.last_mouse_position_x, fps_camera.mouse.last_mouse_position_y);

        // TODO: next step is to then when going back in time grab this and apply it.
        update_number_to_camera_reconstruction_data.emplace(update_number, crd);

        global_logger.start_section("iterating over mouse updates since last tick");
        for (const MouseUpdate &mu : mouse_updates_since_last_tick) {
            global_logger.info("iterating over mouse update: {}", mp.MouseUpdate_to_string(mu));

            fps_camera.mouse_callback(mu.x_pos, mu.y_pos, mu.sensitivity);

            if (mu.fire_pressed) {
                fire_tbs.set_true();
            } else {
                fire_tbs.set_false();
            }

            if (fire_tbs.just_switched_on()) {
                LogSection _(global_logger, "firing logic");

                global_logger.info("we will now restore the physics state to what it was when the user fired");

                JPH::Vec3 current_position = physics_target->GetPosition(), restored_position;

                JPH::StateRecorderImpl current_physics_state;
                physics_target->SaveState(current_physics_state);

                CameraReconstructionData current_crd(
                    fps_camera.transform.get_rotation_yaw(), fps_camera.transform.get_rotation_pitch(),
                    fps_camera.mouse.last_mouse_position_x, fps_camera.mouse.last_mouse_position_y);

                if (subtick_firing_accuracy) {

                    auto jvec3_to_string = [](const JPH::Vec3 &v) {
                        return fmt::format("({}, {}, {})", v.GetX(), v.GetY(), v.GetZ());
                    };

                    LogSection _(global_logger, "subtick firing accuracy");

                    auto t = mu.subtick_percentage_when_fire_pressed;
                    global_logger.debug("subtick percentage when fire pressed: {}", t);

                    auto before_update_number_entity =
                        mu.last_applied_game_update_number_before_firing_entity_interpolation;
                    auto after_update_number_entity = before_update_number_entity + 1;

                    JPH::StateRecorderImpl &physics_state_before_fire_occurred =
                        update_number_to_physics_state.at(before_update_number_entity);
                    JPH::StateRecorderImpl &physics_state_after_fire_occurred =
                        update_number_to_physics_state.at(after_update_number_entity);

                    global_logger.debug("restoring physics state from game update {}", before_update_number_entity);
                    physics_target->RestoreState(physics_state_before_fire_occurred);
                    auto before_firing_position = physics_target->GetPosition();
                    global_logger.debug("position before firing: {}", jvec3_to_string(before_firing_position));

                    global_logger.debug("restoring physics state from game update {}", after_update_number_entity);
                    physics_target->RestoreState(physics_state_after_fire_occurred);
                    auto after_firing_position = physics_target->GetPosition();
                    global_logger.debug("position after firing: {}", jvec3_to_string(after_firing_position));

                    auto target_position_when_firing = (1 - t) * before_firing_position + t * after_firing_position;
                    global_logger.debug("calculated subtick target position when firing: {}",
                                        jvec3_to_string(target_position_when_firing));

                    // restore physics to the pre-fire state (keeping other attributes consistent)
                    physics_target->RestoreState(physics_state_before_fire_occurred);
                    physics_target->SetPosition(target_position_when_firing);
                    restored_position = target_position_when_firing;

                    // camera reconstruction state logging
                    CameraReconstructionData crd_before_fire_occurred = update_number_to_camera_reconstruction_data.at(
                        mu.last_applied_game_update_number_before_firing_camera_cpsr);
                    set_camera_state(crd_before_fire_occurred, fps_camera);

                    global_logger.debug(
                        "camera reconstruction from game update {}: yaw={}, pitch={}, last_mouse_x={}, last_mouse_y={}",
                        mu.last_applied_game_update_number_before_firing_camera_cpsr, crd_before_fire_occurred.yaw,
                        crd_before_fire_occurred.pitch, crd_before_fire_occurred.last_mouse_position_x,
                        crd_before_fire_occurred.last_mouse_position_y);

                    // apply subtick mouse input
                    fps_camera.mouse_callback(mu.subtick_x_pos_before_firing, mu.subtick_y_pos_before_firing,
                                              mu.sensitivity);
                    global_logger.debug("applied subtick mouse callback with x={}, y={}, sensitivity={}",
                                        mu.subtick_x_pos_before_firing, mu.subtick_y_pos_before_firing, mu.sensitivity);
                } else {

                    JPH::StateRecorderImpl &physics_state_when_fire_occurred = update_number_to_physics_state.at(
                        mu.last_applied_game_update_number_before_firing_entity_interpolation);

                    // NOTE: no camera "revert logic" because there is no subtick camera, and wherever the server thinks
                    // it is is correct in this configuration

                    physics_target->RestoreState(physics_state_when_fire_occurred);
                    restored_position = physics_target->GetPosition();
                }

                global_logger.debug("restored target position to: ({}, {}, {}) from position: ({}, {}, {})",
                                    restored_position.GetX(), restored_position.GetY(), restored_position.GetZ(),
                                    current_position.GetX(), current_position.GetY(), current_position.GetZ());

                bool had_hit = run_hitscan_logic(fps_camera, physics_target);
                auto hit_position = physics_target->GetPosition();
                if (had_hit) {

                    global_logger.debug("hit target lagunbfe: {} at: {}, {}, {} with lagunbfc: {} yaw, pitch {}, {}",
                                        mu.last_applied_game_update_number_before_firing_entity_interpolation,
                                        hit_position.GetX(), hit_position.GetY(), hit_position.GetZ(),
                                        mu.last_applied_game_update_number_before_firing_camera_cpsr,
                                        fps_camera.transform.get_rotation_yaw(),
                                        fps_camera.transform.get_rotation_pitch());

                    sphere_orbiter.set_travel_axis(random_unit_vector());
                    sphere_orbiter.set_radius(random_float(room_size / 4, room_size / 2));
                    sphere_orbiter.set_angular_speed(random_float(glm::radians(45.0f), glm::radians(180.0f)));
                    SoundUpdate sound_update(SoundType::SERVER_HIT, 0, 0, 0);
                    sound_updates_this_tick.push_back(sound_update);
                } else {

                    global_logger.debug("missed target lagunbf: {} at: {}, {}, {} with lagunbfc: {} yaw, pitch {}, {}",
                                        mu.last_applied_game_update_number_before_firing_entity_interpolation,
                                        hit_position.GetX(), hit_position.GetY(), hit_position.GetZ(),
                                        mu.last_applied_game_update_number_before_firing_camera_cpsr,
                                        fps_camera.transform.get_rotation_yaw(),
                                        fps_camera.transform.get_rotation_pitch());

                    SoundUpdate sound_update(SoundType::SERVER_MISS, 0, 0, 0);
                    sound_updates_this_tick.push_back(sound_update);
                }

                physics_target->RestoreState(current_physics_state);

                if (subtick_firing_accuracy) {
                    // restore back to original
                    set_camera_state(current_crd, fps_camera);
                }
            }
            last_processed_mouse_pos_update_number = mu.mouse_pos_update_number;
        }
        mouse_updates_since_last_tick.clear();
        global_logger.end_section("iterating over mouse updates since last tick");

        auto target_pos = physics_target->GetPosition();

        GameUpdate gu(last_processed_mouse_pos_update_number, update_number, fps_camera.transform.get_rotation().y,
                      fps_camera.transform.get_rotation().x, target_pos.GetX(), target_pos.GetY(), target_pos.GetZ());

        GameUpdatePacket gup;
        gup.header.type = PacketType::GAME_UPDATE;
        gup.header.size_of_data_without_header = mp.size_when_serialized_GameUpdate(gu);
        gup.game_update = gu;

        // NOTE: what is the point of this check here, why not just broadcast?
        if (network.get_connected_client_ids().size() == 1) {
            auto buffer = mp.serialize_GameUpdatePacket(gup);
            network.unreliable_send(network.get_connected_client_ids().at(0), buffer.data(), buffer.size());
            global_logger.info("just sent game update packet: {}:", mp.GameUpdatePacket_to_string(gup));
        }

        update_number += 1;

        for (const auto &su : sound_updates_this_tick) {
            SoundUpdatePacket sup;
            sup.header.type = PacketType::SOUND_UPDATE;
            sup.header.size_of_data_without_header = mp.size_when_serialized_SoundUpdate(su);
            sup.sound_update = su;

            if (network.get_connected_client_ids().size() == 1) {
                auto buffer = mp.serialize_SoundUpdatePacket(sup);
                network.unreliable_send(network.get_connected_client_ids().at(0), buffer.data(), buffer.size());
                global_logger.info("just sent sound update packet: {}:", mp.SoundUpdatePacket_to_string(sup));
            }
        }
        sound_updates_this_tick.clear();
    };
    std::function<bool()> term = [&]() { return not running; };

    ffl.start(tick, term);

    return 0;
}
