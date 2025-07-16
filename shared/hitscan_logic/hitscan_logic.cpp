#include "hitscan_logic.hpp"

bool run_hitscan_logic(FPSCamera &fps_camera,
                       JPH::Ref<JPH::CharacterVirtual> physics_target) {
  bool had_hit = false;
  JPH::RayCastResult rcr;
  JPH::RayCast aim_ray;
  aim_ray.mOrigin = JPH::Vec3(0, 0, 0);
  aim_ray.mDirection = g2j(fps_camera.transform.compute_forward_vector()) * 100;
  aim_ray.mOrigin -= physics_target->GetPosition();
  had_hit = physics_target->GetShape()->CastRay(aim_ray,
                                                JPH::SubShapeIDCreator(), rcr);
  return had_hit;
}
