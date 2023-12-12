#pragma once
#include <cmath>
#include "core/math/vector.hpp"
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <glm/trigonometric.hpp>
#include <glm/exponential.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/scalar_multiplication.hpp>

namespace Linky
{
using Vec2u = glm::uvec2;
using Vec2i = glm::ivec2;
using Vec2f = glm::vec2;

using Vec3u = glm::uvec3;
using Vec3i = glm::ivec3;
using Vec3f = glm::vec3;

using Vec4i = glm::ivec4;
using Vec4f = glm::vec4;

using Mat4f = glm::mat4;
using Quat = glm::quat;
}