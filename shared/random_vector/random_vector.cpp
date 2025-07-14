#include "random_vector.hpp"

#include <cmath>
#include <glm/gtc/constants.hpp> // for pi
#include <random>

// Returns a random float in the range [min, max)
float random_float(float min, float max) {
  static std::random_device rd;  // seed
  static std::mt19937 gen(rd()); // mersenne twister engine
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen);
}

// Generate a random unit vector in 3D
glm::vec3 random_unit_vector() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  // Uniform distribution for azimuth angle [0, 2π)
  std::uniform_real_distribution<float> dist_azimuth(0.0f,
                                                     2.0f * glm::pi<float>());

  // Uniform distribution for z = cos(theta), to ensure uniform sphere
  // distribution
  std::uniform_real_distribution<float> dist_z(-1.0f, 1.0f);

  float z = dist_z(gen);
  float azimuth = dist_azimuth(gen);
  float r = std::sqrt(1.0f - z * z);
  float x = r * std::cos(azimuth);
  float y = r * std::sin(azimuth);

  return glm::vec3(x, y, z);
}
