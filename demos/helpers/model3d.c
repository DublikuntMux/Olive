#include "assets/tsodinCupLowPoly.h"
#include "olive/math/vec2.h"
#include "olive/math/vec3.h"
#include "vc.c"
#include <olive/olive.h>

#define WIDTH 960
#define HEIGHT 720
#define BACKGROUND_COLOR 0xFF181818

static uint32_t pixels[WIDTH * HEIGHT];
static float zbuffer[WIDTH * HEIGHT] = {0};
static float angle = 0;

void project_2d_scr(vec2 v2, vec2 dest) {
  dest[0] = (v2[0] + 1) / 2 * WIDTH;
  dest[1] = (1 - (v2[1] + 1) / 2) * HEIGHT;
}

Olivec_Canvas vc_render(float dt) {
  angle += 0.25f * PI * dt;

  Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
  olivec_fill(oc, BACKGROUND_COLOR);
  for (size_t i = 0; i < WIDTH * HEIGHT; ++i)
    zbuffer[i] = 0;

  for (size_t i = 0; i < faces_count; ++i) {
    int a = faces[i][0];
    int b = faces[i][1];
    int c = faces[i][2];

    vec3 v1 = {vertices[a][0], vertices[a][1], vertices[a][2]};
    olive_vec3_rotate(v1, angle, OLIVE_YUP);

    vec3 v2 = {vertices[b][0], vertices[b][1], vertices[b][2]};
    olive_vec3_rotate(v2, angle, OLIVE_YUP);

    vec3 v3 = {vertices[c][0], vertices[c][1], vertices[c][2]};
    olive_vec3_rotate(v3, angle, OLIVE_YUP);

    v1[2] += 1.5f;
    v2[2] += 1.5f;
    v3[2] += 1.5f;

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

    int lx, hx, ly, hy;
    if (olivec_normalize_triangle(oc.width, oc.height, p1[0], p1[1], p2[0],
                                  p2[1], p3[0], p3[1], &lx, &hx, &ly, &hy)) {
      for (int y = ly; y <= hy; ++y) {
        for (int x = lx; x <= hx; ++x) {
          int u1, u2, det;
          if (olivec_barycentric(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], x, y,
                                 &u1, &u2, &det)) {
            int u3 = det - u1 - u2;
            float z = 1 / v1[2] * u1 / det + 1 / v2[2] * u2 / det +
                      1 / v3[2] * u3 / det;
            float near = 0.1f;
            float far = 5.0f;
            if (1.0f / far < z && z < 1.0f / near &&
                z > zbuffer[y * WIDTH + x]) {
              zbuffer[y * WIDTH + x] = z;
              OLIVEC_PIXEL(oc, x, y) =
                  mix_colors3(0xFF1818FF, 0xFF18FF18, 0xFFFF1818, u1, u2, det);

              z = 1.0f / z;
              if (z >= 1.0) {
                z -= 1.0f;
                uint32_t v = z * 255;
                if (v > 255)
                  v = 255;
                olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), (v << (3 * 8)));
              }
            }
          }
        }
      }
    }
  }

  return oc;
}
