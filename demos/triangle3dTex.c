#include "./assets/lavastone.h"
#include "./assets/oldstone.h"
#include "./assets/tsodinPog.h"
#include "helpers/vc.c"
#include <math.h>
#include <olive/olive.h>

#define WIDTH 960
#define HEIGHT 720

static uint32_t pixels1[WIDTH * HEIGHT];
static float zbuffer1[WIDTH * HEIGHT];
static uint32_t pixels2[WIDTH * HEIGHT];
static float zbuffer2[WIDTH * HEIGHT];

void project_2d_scr(vec2 v2, vec2 dest) {
  dest[0] = (v2[0] + 1) / 2 * WIDTH;
  dest[1] = (1 - (v2[1] + 1) / 2) * HEIGHT;
}

static float global_time = 1.0f;

Olivec_Canvas vc_render(float dt) {
  global_time += dt;

  Olivec_Canvas oc1 = olivec_canvas(pixels1, WIDTH, HEIGHT, WIDTH);
  olivec_fill(oc1, 0xFF181818);
  Olivec_Canvas zb1 = olivec_canvas((uint32_t *)zbuffer1, WIDTH, HEIGHT, WIDTH);
  olivec_fill(zb1, 0);

  Olivec_Canvas oldstone = olivec_canvas(oldstone_pixels, oldstone_width,
                                         oldstone_height, oldstone_width);
  Olivec_Canvas lavastone = olivec_canvas(lavastone_pixels, lavastone_width,
                                          lavastone_height, lavastone_width);

  float z = 1.5f;
  float t = 0.75f;
  {
    vec3 v1 = {cosf(global_time) * t, -t, z + sinf(global_time) * t};
    vec3 v2 = {cosf(global_time + PI) * t, -t, z + sinf(global_time + PI) * t};
    vec3 v3 = {0, t, z};

    vec2 p1 = OLIVE_VEC2_ONE_INIT;
    vec2 d1 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v1, d1);
    project_2d_scr(d1, p1);

    vec2 p2 = OLIVE_VEC2_ONE_INIT;
    vec2 d2 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v2, d2);
    project_2d_scr(d2, p2);

    vec2 p3 = OLIVE_VEC2_ONE_INIT;
    vec2 d3 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v3, d3);
    project_2d_scr(d3, p3);

    olivec_triangle3uv_bilinear(oc1, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1],
                                0 / v1[2], 1 / v1[2], 1 / v2[2], 1 / v2[2],
                                0.5 / v3[2], 0 / v3[2], 1 / v1[2], 1 / v2[2],
                                1 / v3[2], oldstone);
    olivec_triangle3z(zb1, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1],
                      1.0f / v1[2], 1.0f / v2[2], 1.0f / v3[2]);
  }

  Olivec_Canvas oc2 = olivec_canvas(pixels2, WIDTH, HEIGHT, WIDTH);
  olivec_fill(oc2, 0xFF181818);
  Olivec_Canvas zb2 = olivec_canvas((uint32_t *)zbuffer2, WIDTH, HEIGHT, WIDTH);
  olivec_fill(zb2, 0);

  {
    vec3 v1 = {cosf(global_time + PI / 2) * t, -t,
               z + sinf(global_time + PI / 2) * t};
    vec3 v2 = {cosf(global_time + PI + PI / 2) * t, -t,
               z + sinf(global_time + PI + PI / 2) * t};
    vec3 v3 = {0, t, z};

    vec2 p1 = OLIVE_VEC2_ONE_INIT;
    vec2 d1 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v1, d1);
    project_2d_scr(d1, p1);

    vec2 p2 = OLIVE_VEC2_ONE_INIT;
    vec2 d2 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v2, d2);
    project_2d_scr(d2, p2);

    vec2 p3 = OLIVE_VEC2_ONE_INIT;
    vec2 d3 = OLIVE_VEC2_ONE_INIT;
    olive_project_3d_2d(v3, d3);
    project_2d_scr(d3, p3);

    olivec_triangle3uv_bilinear(oc2, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1],
                                0 / v1[2], 1 / v1[2], 1 / v2[2], 1 / v2[2],
                                0.5 / v3[2], 0 / v3[2], 1 / v1[2], 1 / v2[2],
                                1 / v3[2], lavastone);

    olivec_triangle3z(zb2, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1],
                      1.0f / v1[2], 1.0f / v2[2], 1.0f / v3[2]);
  }

  for (size_t y = 0; y < HEIGHT; ++y) {
    for (size_t x = 0; x < WIDTH; ++x) {
      float z1 = *(float *)&OLIVEC_PIXEL(zb1, x, y);
      float z2 = *(float *)&OLIVEC_PIXEL(zb2, x, y);
      if (z1 < z2) {
        OLIVEC_PIXEL(oc1, x, y) = OLIVEC_PIXEL(oc2, x, y);
        z1 = z2;
      }
      z1 = 1.0f / z1;
      if (z1 >= 1.0) {
        z1 -= 1.0f;
        uint32_t v = z1 * 255;
        if (v > 255)
          v = 255;
        olivec_blend_color(&OLIVEC_PIXEL(oc1, x, y), (v << (3 * 8)));
      }
    }
  }

  return oc1;
}
