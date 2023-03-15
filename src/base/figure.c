#include "olive/base/figure.h"
#include "olive/base/color.h"
#include "olive/base/tringle.h"
#include "olive/math/utils.h"
#include "olive/types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void olivec_rect(Olivec_Canvas oc, int x, int y, int w, int h, uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;
  for (int i = nr.x1; i <= nr.x2; ++i) {
    for (int ii = nr.y1; ii <= nr.y2; ++ii) {
      olivec_blend_color(&OLIVEC_PIXEL(oc, i, ii), color);
    }
  }
}

bool olivec_normalize_rect(int x, int y, int w, int h, size_t canvas_width,
                           size_t canvas_height, Olivec_Normalized_Rect *nr) {
  if (w == 0)
    return false;
  if (h == 0)
    return false;

  nr->ox1 = x;
  nr->oy1 = y;

  nr->ox2 = nr->ox1 + olive_sign(w) * (abs(w) - 1);
  if (nr->ox1 > nr->ox2)
    olive_swap(&nr->ox1, &nr->ox2);
  nr->oy2 = nr->oy1 + olive_sign(h) * (abs(h) - 1);
  if (nr->oy1 > nr->oy2)
    olive_swap(&nr->oy1, &nr->oy2);

  if (nr->ox1 >= (int)canvas_width)
    return false;
  if (nr->ox2 < 0)
    return false;
  if (nr->oy1 >= (int)canvas_height)
    return false;
  if (nr->oy2 < 0)
    return false;

  nr->x1 = nr->ox1;
  nr->y1 = nr->oy1;
  nr->x2 = nr->ox2;
  nr->y2 = nr->oy2;

  if (nr->x1 < 0)
    nr->x1 = 0;
  if (nr->x2 >= (int)canvas_width)
    nr->x2 = (int)canvas_width - 1;
  if (nr->y1 < 0)
    nr->y1 = 0;
  if (nr->y2 >= (int)canvas_height)
    nr->y2 = (int)canvas_height - 1;

  return true;
}

void olivec_frame(Olivec_Canvas oc, int x, int y, int w, int h, size_t t,
                  uint32_t color) {
  if (t == 0)
    return;

  int x1 = x;
  int y1 = y;

  int x2 = x1 + olive_sign(w) * (abs(w) - 1);
  if (x1 > x2)
    olive_swap(&x1, &x2);
  int y2 = y1 + olive_sign(h) * (abs(h) - 1);
  if (y1 > y2)
    olive_swap(&y1, &y2);

  olivec_rect(oc, x1 - t / 2, y1 - t / 2, (x2 - x1 + 1) + t / 2 * 2, t,
              color); // Top
  olivec_rect(oc, x1 - t / 2, y1 - t / 2, t, (y2 - y1 + 1) + t / 2 * 2,
              color); // Left
  olivec_rect(oc, x1 - t / 2, y2 + t / 2, (x2 - x1 + 1) + t / 2 * 2, -t,
              color); // Bottom
  olivec_rect(oc, x2 + t / 2, y1 - t / 2, -t, (y2 - y1 + 1) + t / 2 * 2,
              color); // Right
}

void olivec_ellipse(Olivec_Canvas oc, int cx, int cy, int rx, int ry,
                    uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  int rx1 = rx + olive_sign(rx);
  int ry1 = ry + olive_sign(ry);
  if (!olivec_normalize_rect(cx - rx1, cy - ry1, 2 * rx1, 2 * ry1, oc.width,
                             oc.height, &nr))
    return;

  for (int y = nr.y1; y <= nr.y2; ++y) {
    for (int x = nr.x1; x <= nr.x2; ++x) {
      float nx = (x + 0.5 - nr.x1) / (2.0f * rx1);
      float ny = (y + 0.5 - nr.y1) / (2.0f * ry1);
      float dx = nx - 0.5;
      float dy = ny - 0.5;
      if (dx * dx + dy * dy <= 0.5 * 0.5) {
        OLIVEC_PIXEL(oc, x, y) = color;
      }
    }
  }
}

void olivec_circle(Olivec_Canvas oc, int cx, int cy, int r, uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  int r1 = r + olive_sign(r);
  if (!olivec_normalize_rect(cx - r1, cy - r1, 2 * r1, 2 * r1, oc.width,
                             oc.height, &nr))
    return;

  for (int y = nr.y1; y <= nr.y2; ++y) {
    for (int x = nr.x1; x <= nr.x2; ++x) {
      int count = 0;
      for (int sox = 0; sox < OLIVEC_AA_RES; ++sox) {
        for (int soy = 0; soy < OLIVEC_AA_RES; ++soy) {
          int res1 = (OLIVEC_AA_RES + 1);
          int dx = (x * res1 * 2 + 2 + sox * 2 - res1 * cx * 2 - res1);
          int dy = (y * res1 * 2 + 2 + soy * 2 - res1 * cy * 2 - res1);
          if (dx * dx + dy * dy <= res1 * res1 * r * r * 2 * 2)
            count += 1;
        }
      }
      uint32_t alpha = ((color & 0xFF000000) >> (3 * 8)) * count /
                       OLIVEC_AA_RES / OLIVEC_AA_RES;
      uint32_t updated_color = (color & 0x00FFFFFF) | (alpha << (3 * 8));
      olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), updated_color);
    }
  }
}

// TODO: AA for line
// TODO: lines with different thiccness
void olivec_line(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                 uint32_t color) {
  int dx = x2 - x1;
  int dy = y2 - y1;

  if (dx == 0 && dy == 0) {
    if (0 <= x1 && x1 < (int)oc.width && 0 <= y1 && y1 < (int)oc.height) {
      olivec_blend_color(&OLIVEC_PIXEL(oc, x1, y1), color);
    }
    return;
  }

  if (abs(dx) > abs(dy)) {
    if (x1 > x2) {
      olive_swap(&x1, &x2);
      olive_swap(&y1, &y2);
    }

    if (x1 > (int)oc.width)
      return;
    if (x2 < 0)
      return;
    if (x1 < 0)
      x1 = 0;
    if (x2 >= (int)oc.width)
      x2 = (int)oc.width - 1;

    for (int x = x1; x <= x2; ++x) {
      int y = dy * (x - x1) / dx + y1;
      if (0 <= y && y < (int)oc.height) {
        olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
      }
    }
  } else {
    if (y1 > y2) {
      olive_swap(&x1, &x2);
      olive_swap(&y1, &y2);
    }

    if (y1 > (int)oc.height)
      return;
    if (y2 < 0)
      return;
    if (y1 < 0)
      y1 = 0;
    if (y2 >= (int)oc.height)
      y2 = (int)oc.height - 1;

    for (int y = y1; y <= y2; ++y) {
      int x = dx * (y - y1) / dy + x1;
      if (0 <= x && x < (int)oc.width) {
        olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
      }
    }
  }
}

// TODO: AA for triangle
void olivec_triangle(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                     int y3, uint32_t color) {
  int lx, hx, ly, hy;
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
        }
      }
    }
  }
}
