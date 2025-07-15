#include <iostream>
#include <vector>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/RayCast.h>

#include <glm/fwd.hpp>

#include "networking/packet_handler/packet_handler.hpp"
#include "networking/packets/packets.hpp"
#include "networking/server_networking/network.hpp"

#include "graphics/fps_camera/fps_camera.hpp"

#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/temporal_binary_switch/temporal_binary_switch.hpp"
#include "utility/jolt_glm_type_conversions/jolt_glm_type_conversions.hpp"

#include "system_logic/physics/physics.hpp"
#include "system_logic/random_vector/random_vector.hpp"
#include "system_logic/sphere_orbiter/sphere_orbiter.hpp"
#include "system_logic/mouse_update_logger/mouse_update_logger.hpp"

int main() {

    // TODO: get a packet handler in here, make a mouse update packet and then
    // move aiming logic onto the server, then we work on client and make it feel
    // good.

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
    network.initialize_network();

    MouseUpdateLogger mouse_update_logger;

    PacketHandler packet_handler;

    TemporalBinarySwitch fire_tbs;

    std::vector<MouseUpdate> mouse_updates_since_last_tick;

    std::function<void(const void *)> mouse_update_handler = [&](const void *data) {
        const MouseUpdatePacket *packet = reinterpret_cast<const MouseUpdatePacket *>(data);
        MouseUpdate just_received_mouse_update = packet->mouse_update;
        mouse_updates_since_last_tick.push_back(just_received_mouse_update);
    };

    packet_handler.register_handler(PacketType::MOUSE_UPDATE, mouse_update_handler);

    std::function<void(double)> tick = [&](double dt) {
        std::vector<PacketWithSize> pws = network.get_network_events_since_last_tick();
        packet_handler.handle_packets(pws);

        for (const MouseUpdate &mu : mouse_updates_since_last_tick) {

            fps_camera.mouse_callback(mu.x_pos, mu.y_pos, mu.sensitivity);
            mouse_update_logger.log(mu.x_pos, mu.y_pos, mu.mouse_pos_update_number, fps_camera);

            if (mu.fire_pressed) {
                fire_tbs.set_true();
            } else {
                fire_tbs.set_false();
            }

            auto new_pos = sphere_orbiter.process(dt);
            physics_target->SetPosition(g2j(new_pos));

            // hitscan logic [[

            if (fire_tbs.just_switched_on()) {
                JPH::RayCastResult rcr;
                JPH::RayCast aim_ray;
                aim_ray.mOrigin = JPH::Vec3(0, 0, 0);
                aim_ray.mDirection = g2j(fps_camera.transform.compute_forward_vector()) * 100;
                aim_ray.mOrigin -= physics_target->GetPosition();
                bool hit = physics_target->GetShape()->CastRay(aim_ray, JPH::SubShapeIDCreator(), rcr);
                if (hit) {
                    std::cout << "hit target" << std::endl;
                    sphere_orbiter.set_travel_axis(random_unit_vector());
                    sphere_orbiter.set_radius(random_float(room_size / 4, room_size / 2));
                    sphere_orbiter.set_angular_speed(random_float(glm::radians(45.0f), glm::radians(180.0f)));
                }
            }

            // hitscan logic ]]

            last_processed_mouse_pos_update_number = mu.mouse_pos_update_number;
        }
        mouse_updates_since_last_tick.clear();

        auto target_pos = physics_target->GetPosition();

        GameUpdate gu(last_processed_mouse_pos_update_number, fps_camera.transform.get_rotation().y,
                      fps_camera.transform.get_rotation().x, target_pos.GetX(), target_pos.GetY(), target_pos.GetZ());

        GameUpdatePacket gup;
        gup.header.type = PacketType::GAME_UPDATE;
        gup.header.size_of_data_without_header = sizeof(GameUpdate);
        gup.game_update = gu;

        if (network.get_connected_client_ids().size() == 1) {
            network.unreliable_send(network.get_connected_client_ids().at(0), &gup, sizeof(GameUpdatePacket));
        }
    };
    std::function<bool()> term = [&]() { return not running; };

    ffl.start(tick, term);

    return 0;
}
