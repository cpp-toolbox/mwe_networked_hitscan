#ifndef MOUSE_UPDATE_LOGGER
#define MOUSE_UPDATE_LOGGER

class MouseUpdateLogger {
  ConsoleLogger logger{"mouse_update_logger"};

  void log(MouseUpdate mu, FPSCamera fps_camera) {
    std::cout << "after processing " << mu
              << " we got yaw: " << fps_camera.transform.get_rotation_yaw()
              << " and pitch " << fps_camera.transform.get_rotation_pitch()
              << std::endl;
  }
};

#endif // MOUSE_UPDATE_LOGGER
