#include "olive/math/vec.h"
#include <math.h>

#define EPSILON 1e-6

/**
 * @brief Make a 2D vector.
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @return A vector with the given values.
 */
vec2 make_vec2(float x, float y) {
  vec2 v2;
  v2.x = x;
  v2.y = y;
  return v2;
}

/**
 * @brief Project a 3D vector onto a 2D vector.
 * @param v3 The vector to project.
 * @return The projected vector.
 */
vec2 project_3d_2d(vec3 v3) {
  if (v3.z < 0)
    v3.z = -v3.z;
  if (v3.z < EPSILON)
    v3.z += EPSILON;
  return make_vec2(v3.x / v3.z, v3.y / v3.z);
}

/**
 * @brief Rotates a vector around the x axis by delta_angle.
 * @param p The vector to rotate around.
 * @param delta_angle The amount by which to rotate the vector (in radians).
 * @return A vector with the rotated vector in x - direction.
 */
vec2 vec2_rotate_x(vec2 p, float delta_angle) {
  float angle = atanf(p.y) + delta_angle;
  float mag = sqrtf(p.y * p.y);
  return make_vec2(cosf(angle) * mag, p.y);
}

/**
 * @brief Rotates a vector around the y axis by delta_angle.
 * @param p The vector to rotate around.
 * @param delta_angle The amount by which to rotate the vector (in radians).
 * @return A vector with the rotated vector in y - direction.
 */
vec2 vec2_rotate_y(vec2 p, float delta_angle) {
  float angle = atanf(p.x) + delta_angle;
  float mag = sqrtf(p.x * p.x);
  return make_vec2(p.x, cosf(angle) * mag);
}

/**
 * @brief Make a 3 - component vector.
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @return A vector with the given values.
 */
vec3 make_vec3(float x, float y, float z) {
  vec3 v3;
  v3.x = x;
  v3.y = y;
  v3.z = z;
  return v3;
}

/**
 * @brief Rotates a vector around the y axis by delta_angle.
 * @param p The vector to rotate around.
 * @param delta_angle The amount by which to rotate the vector (in radians).
 * @return A vec3 with the rotated vector in y - direction.
 */
vec3 vec3_rotate_y(vec3 p, float delta_angle) {
  float angle = atan2f(p.z, p.x) + delta_angle;
  float mag = sqrtf(p.x * p.x + p.z * p.z);
  return make_vec3(cosf(angle) * mag, p.y, sinf(angle) * mag);
}

/**
 * @brief Rotates a vector around the x axis by delta_angle.
 * @param p The vector to rotate around.
 * @param delta_angle The amount by which to rotate the vector (in radians).
 * @return A vec3 with the rotated vector in x - direction.
 */
vec3 vec3_rotate_x(vec3 p, float delta_angle) {
  float angle = atan2f(p.y, p.z) + delta_angle;
  float mag = sqrtf(p.z * p.z + p.y * p.y);
  return make_vec3(p.x, cosf(angle) * mag, sinf(angle) * mag);
}

/**
 * @brief Rotates a vector around the z axis by delta_angle.
 * @param p The vector to rotate around.
 * @param delta_angle The amount by which to rotate the vector (in radians).
 * @return A vec3 with the rotated vector in z - direction.
 */
vec3 vec3_rotate_z(vec3 p, float delta_angle) {
  float angle = atan2f(p.y, p.x) + delta_angle;
  float mag = sqrtf(p.x * p.x + p.y * p.y);
  return make_vec3(cosf(angle) * mag, sinf(angle) * mag, p.z);
}
