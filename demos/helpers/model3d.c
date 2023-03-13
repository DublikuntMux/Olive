#include "vc.c"
#include <olive/base/tringle.h>
#include <olive/base/color.h>
#include <olive/math/vec.h>

#define WIDTH 960
#define HEIGHT 720
#define BACKGROUND_COLOR 0xFF181818

#define PI 3.14159265359

static uint32_t pixels[WIDTH * HEIGHT];
static float zbuffer[WIDTH * HEIGHT] = {0};
static float angle = 0;

static vec2 project_2d_scr(vec2 v2) {
  return make_vec2((v2.x + 1) / 2 * WIDTH, (1 - (v2.y + 1) / 2) * HEIGHT);
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
    vec3 v1 = vec3_rotate_y(
        make_vec3(vertices[a][0], vertices[a][1], vertices[a][2]), angle);
    vec3 v2 = vec3_rotate_y(
        make_vec3(vertices[b][0], vertices[b][1], vertices[b][2]), angle);
    vec3 v3 = vec3_rotate_y(
        make_vec3(vertices[c][0], vertices[c][1], vertices[c][2]), angle);
    v1.z += 1.5f;
    v2.z += 1.5f;
    v3.z += 1.5f;
    vec2 p1 = project_2d_scr(project_3d_2d(v1));
    vec2 p2 = project_2d_scr(project_3d_2d(v2));
    vec2 p3 = project_2d_scr(project_3d_2d(v3));

    int x1 = p1.x;
    int x2 = p2.x;
    int x3 = p3.x;
    int y1 = p1.y;
    int y2 = p2.y;
    int y3 = p3.y;
    int lx, hx, ly, hy;
    if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                  &lx, &hx, &ly, &hy)) {
      for (int y = ly; y <= hy; ++y) {
        for (int x = lx; x <= hx; ++x) {
          int u1, u2, det;
          if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2,
                                 &det)) {
            int u3 = det - u1 - u2;
            float z =
                1 / v1.z * u1 / det + 1 / v2.z * u2 / det + 1 / v3.z * u3 / det;
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
