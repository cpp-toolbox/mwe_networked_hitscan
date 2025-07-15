#ifndef SPHERE_ORBITER_HPP
#define SPHERE_ORBITER_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class SphereOrbiter {
public:
  // Constructor with default values for all parameters
  SphereOrbiter(glm::vec3 center = glm::vec3(0.0f), float radius = 1.0f,
                glm::vec3 travel_axis = glm::vec3(0.0f, 1.0f, 0.0f),
                float angular_speed_rad_per_sec = glm::radians(90.0f),
                float initial_angle = 0.0f)
      : center(center), radius(radius),
        angular_speed(angular_speed_rad_per_sec), angle(initial_angle) {
    this->travel_axis = glm::normalize(travel_axis);

    set_travel_axis(travel_axis);
  }

  // Advance the orbit and return the new position
  glm::vec3 process(float dt) {
    angle += angular_speed * dt;
    glm::vec3 rotated = glm::rotate(orbit_vector, angle, travel_axis);
    return center + rotated;
  }

  void set_travel_axis(const glm::vec3 &travel_axis) {
    this->travel_axis = travel_axis;
    // Choose arbitrary initial vector orthogonal to travel_axis
    glm::vec3 fallback = glm::vec3(0.0f, 1.0f, 0.0f);
    if (glm::abs(glm::dot(fallback, this->travel_axis)) > 0.99f)
      fallback = glm::vec3(1.0f, 0.0f, 0.0f);

    orbit_vector = glm::normalize(glm::cross(travel_axis, fallback)) * radius;
  }

  void set_radius(const float &radius) { this->radius = radius; }
  void set_angular_speed(const float &angular_speed) {
    this->angular_speed = angular_speed;
  }

private:
  glm::vec3 center;
  float radius;
  glm::vec3 travel_axis;
  glm::vec3 orbit_vector;
  float angle;
  float angular_speed;
};

#endif // SPHERE_ORBITER_HPP
