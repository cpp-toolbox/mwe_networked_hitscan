#ifndef PACKETS_HPP
#define PACKETS_HPP

#include "../../sound/sound_types/sound_types.hpp"
#include "../packet_data/packet_data.hpp"

#include <iostream>

struct MouseUpdate {
  unsigned int mouse_pos_update_number;
  // subtick specific stuff

  // NOTE: the two game updates below are not always synchronized, when entity
  // interpolation is turned on then its last applied game update number will be
  // smaller then the one for the camera, that's because entities rendering is
  // delayed so that we can interpolate
  unsigned int
      last_applied_game_update_number_before_firing_entity_interpolation;
  // NOTE: this game update number is the one that we use during cpsr on the
  // camera, it more "up to date" then the entity number because we want to stay
  // as synchronized with the server as possible
  unsigned int last_applied_game_update_number_before_firing_camera_cpsr;

  double subtick_percentage_when_fire_pressed;
  // NOTE: these are required because yaw pitch has to be adjusted as well as
  // target position during server revert
  double subtick_x_pos_before_firing;
  double subtick_y_pos_before_firing;
  // regular stuff
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
