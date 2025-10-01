#ifndef PACKETS_HPP
#define PACKETS_HPP

#include "../../sound/sound_types/sound_types.hpp"
#include "../packet_data/packet_data.hpp"

#include <iostream>

struct MouseUpdate {
    unsigned int mouse_pos_update_number;
    unsigned int last_applied_game_update_number;
    double x_pos;
    double y_pos;
    bool fire_pressed;
    double sensitivity;
};

struct GameUpdate {
    unsigned int last_processed_mouse_pos_update_number;
    unsigned int update_number;
    double yaw;
    double pitch;
    double target_x_pos;
    double target_y_pos;
    double target_z_pos;
};

struct SoundUpdate {
    SoundType sound_to_play;
    double x;
    double y;
    double z;
};

struct MouseUpdatePacket {
    PacketHeader header;
    MouseUpdate mouse_update;
};

struct GameUpdatePacket {
    PacketHeader header;
    GameUpdate game_update;
};

struct SoundUpdatePacket {
    PacketHeader header;
    SoundUpdate sound_update;
};

#endif // PACKETS_HPP
