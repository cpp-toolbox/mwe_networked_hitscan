#include <iostream>

#include "networking/server_networking/network.hpp"
#include "networking/packet_handler/packet_handler.hpp"
#include "networking/packets/packets.hpp"

#include "graphics/fps_camera/fps_camera.hpp"

#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"

#include "system_logic/physics/physics.hpp"

class GameUpdate {
    unsigned int last_processed_update_number;
    double yaw;
    double pitch;
};

int main() {
    // TODO: get a packet handler in here, make a mouse update packet and then
    // move aiming logic onto the server, then we work on client and make it feel good.

    bool running = true;
    unsigned int last_processed_update_number = 0;

    FixedFrequencyLoop ffl;
    Physics physics;

    FPSCamera fps_camera;

    Network network(7777);
    PacketHandler packet_handler;

    // TODO: next we want a command runner to change sens, also we need the orbit code on the server now as well
    // so we kinda need/want a shared folder thing going on this is true ,we can just use copy utilities instead of
    // symlinks.

    std::function<void(const void *)> mouse_update_handler = [&](const void *data) {
        const MouseUpdatePacket *packet = reinterpret_cast<const MouseUpdatePacket *>(data);
        MouseUpdate just_received_mouse_update = packet->mouse_update;

        fps_camera.mouse_callback(packet->mouse_update.x_pos, packet->mouse_update.y_pos,
                                  packet->mouse_update.sensitivity);

        last_processed_update_number = packet->mouse_update.update_number;
    };

    auto physics_target = physics.create_character(0);

    std::function<void(double)> tick = [](double dt) { std::cout << "tick" << std::endl; };
    std::function<bool()> term = [&]() { return not running; };

    ffl.start(tick, term);

    return 0;
}
