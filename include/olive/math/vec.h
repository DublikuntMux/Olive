#ifndef OLIVE_VEC_H
#define OLIVE_VEC_H

typedef struct {
  float x, y;
} vec2;

typedef struct {
  float x, y, z;
} vec3;

typedef struct {
  float x, y, z, w;
} vec4;

vec2 make_vec2(float x, float y);
vec2 project_3d_2d(vec3 v3);
vec2 vec2_rotate_x(vec2 p, float delta_angle);
vec2 vec2_rotate_y(vec2 p, float delta_angle);

vec3 make_vec3(float x, float y, float z);
vec3 vec3_rotate_x(vec3 p, float delta_angle);
vec3 vec3_rotate_y(vec3 p, float delta_angle);
vec3 vec3_rotate_z(vec3 p, float delta_angle);

vec4 make_vec4(float x, float y, float z, float w);
vec4 vec4_rotate_x(vec4 p, float delta_angle);
vec4 vec4_rotate_y(vec4 p, float delta_angle);
vec4 vec4_rotate_z(vec4 p, float delta_angle);
vec4 vec4_rotate_w(vec4 p, float delta_angle);

#endif // OLIVE_VEC_H
