#ifndef MOUSE_UPDATE_LOGGER
#define MOUSE_UPDATE_LOGGER

class MouseUpdateLogger {
public:
  ConsoleLogger logger{"mouse_update_logger"};

  void log(double xpos, double ypos, unsigned int mouse_pos_update_number,
           FPSCamera &fps_camera) {
    std::cout << "after processing [" << mouse_pos_update_number << "] " << xpos
              << ", " << ypos
              << " we got yaw: " << fps_camera.transform.get_rotation_yaw()
              << " and pitch " << fps_camera.transform.get_rotation_pitch()
              << std::endl;
  }
};

#endif // MOUSE_UPDATE_LOGGER
