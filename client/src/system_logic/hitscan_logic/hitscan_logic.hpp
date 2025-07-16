#ifndef HITSCAN_LOGIC_HPP
#define HITSCAN_LOGIC_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

#include "../../graphics/fps_camera/fps_camera.hpp"
#include "../../utility/jolt_glm_type_conversions/jolt_glm_type_conversions.hpp"

bool run_hitscan_logic(FPSCamera &fps_camera,
                       JPH::Ref<JPH::CharacterVirtual> physics_target);

#endif // HITSCAN_LOGIC_HPP
