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
    std::unordered_map<unsigned int, JPH::StateRecorderImpl> update_number_to_physics_state;

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

                JPH::StateRecorderImpl current_physics_state;
                physics_target->SaveState(current_physics_state);

                JPH::StateRecorderImpl &physics_state_when_fire_occurred =
                    update_number_to_physics_state.at(mu.last_applied_game_update_number);

                auto before_position = physics_target->GetPosition();
                physics_target->RestoreState(physics_state_when_fire_occurred);
                auto restored_position = physics_target->GetPosition();

                global_logger.debug("restored target position to: ({}, {}, {}) from position: ({}, {}, {})",
                                    restored_position.GetX(), restored_position.GetY(), restored_position.GetZ(),
                                    before_position.GetX(), before_position.GetY(), before_position.GetZ());

                bool had_hit = run_hitscan_logic(fps_camera, physics_target);
                auto hit_position = physics_target->GetPosition();
                if (had_hit) {

                    global_logger.debug("hit target lagun: {} at: {}, {}, {} with yaw, pitch {}, {}",
                                        mu.last_applied_game_update_number, hit_position.GetX(), hit_position.GetY(),
                                        hit_position.GetZ(), fps_camera.transform.get_rotation_yaw(),
                                        fps_camera.transform.get_rotation_pitch());

                    sphere_orbiter.set_travel_axis(random_unit_vector());
                    sphere_orbiter.set_radius(random_float(room_size / 4, room_size / 2));
                    sphere_orbiter.set_angular_speed(random_float(glm::radians(45.0f), glm::radians(180.0f)));
                    SoundUpdate sound_update(SoundType::SERVER_HIT, 0, 0, 0);
                    sound_updates_this_tick.push_back(sound_update);
                } else {

                    global_logger.debug("missed target lagun: {} at: {}, {}, {} with yaw, pitch {}, {}",
                                        mu.last_applied_game_update_number, hit_position.GetX(), hit_position.GetY(),
                                        hit_position.GetZ(), fps_camera.transform.get_rotation_yaw(),
                                        fps_camera.transform.get_rotation_pitch());

                    SoundUpdate sound_update(SoundType::SERVER_MISS, 0, 0, 0);
                    sound_updates_this_tick.push_back(sound_update);
                }

                physics_target->RestoreState(current_physics_state);
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
