#ifndef MOUSE_UPDATE_LOGGER
#define MOUSE_UPDATE_LOGGER

#include "../../networking/packets/packets.hpp"

class MouseUpdateLogger {
public:
  ConsoleLogger logger{"mouse_update_logger"};

  void log_game_update(GameUpdate &gu) {
    logger.debug("just received yaw: {} pitch: {} lpmu: {}", gu.yaw, gu.pitch,
                 gu.last_processed_mouse_pos_update_number);
  }

  void log(double xpos, double ypos, unsigned int mouse_pos_update_number,
           FPSCamera &fps_camera) {
    logger.debug(
        "after processing [{}]: ({}, {}) we produced yaw pitch: ({}, {})",
        mouse_pos_update_number, xpos, ypos,
        fps_camera.transform.get_rotation_yaw(),
        fps_camera.transform.get_rotation_pitch());
  }
};

#endif // MOUSE_UPDATE_LOGGER
