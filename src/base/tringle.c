OLIVECDEF bool olivec_normalize_triangle(size_t width, size_t height, int x1,
                                         int y1, int x2, int y2, int x3, int y3,
                                         int *lx, int *hx, int *ly, int *hy) {
  *lx = x1;
  *hx = x1;
  if (*lx > x2)
    *lx = x2;
  if (*lx > x3)
    *lx = x3;
  if (*hx < x2)
    *hx = x2;
  if (*hx < x3)
    *hx = x3;
  if (*lx < 0)
    *lx = 0;
  if ((size_t)*lx >= width)
    return false;
  ;
  if (*hx < 0)
    return false;
  ;
  if ((size_t)*hx >= width)
    *hx = width - 1;

  *ly = y1;
  *hy = y1;
  if (*ly > y2)
    *ly = y2;
  if (*ly > y3)
    *ly = y3;
  if (*hy < y2)
    *hy = y2;
  if (*hy < y3)
    *hy = y3;
  if (*ly < 0)
    *ly = 0;
  if ((size_t)*ly >= height)
    return false;
  ;
  if (*hy < 0)
    return false;
  ;
  if ((size_t)*hy >= height)
    *hy = height - 1;

  return true;
}

OLIVECDEF void olivec_triangle3c(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, uint32_t c1,
                                 uint32_t c2, uint32_t c3) {
  int lx, hx, ly, hy;
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          olivec_blend_color(&OLIVEC_PIXEL(oc, x, y),
                             mix_colors3(c1, c2, c3, u1, u2, det));
        }
      }
    }
  }
}

OLIVECDEF void olivec_triangle3z(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, float z1, float z2,
                                 float z3) {
  int lx, hx, ly, hy;
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          OLIVEC_PIXEL(oc, x, y) = *(uint32_t *)&z;
        }
      }
    }
  }
}

OLIVECDEF void olivec_triangle3uv(Olivec_Canvas oc, int x1, int y1, int x2,
                                  int y2, int x3, int y3, float tx1, float ty1,
                                  float tx2, float ty2, float tx3, float ty3,
                                  float z1, float z2, float z3,
                                  Olivec_Canvas texture) {
  int lx, hx, ly, hy;
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          int u3 = det - u1 - u2;
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
          float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

          int texture_x = tx / z * texture.width;
          if (texture_x < 0)
            texture_x = 0;
          if ((size_t)texture_x >= texture.width)
            texture_x = texture.width - 1;

          int texture_y = ty / z * texture.height;
          if (texture_y < 0)
            texture_y = 0;
          if ((size_t)texture_y >= texture.height)
            texture_y = texture.height - 1;
          OLIVEC_PIXEL(oc, x, y) =
              OLIVEC_PIXEL(texture, (int)texture_x, (int)texture_y);
        }
      }
    }
  }
}

OLIVECDEF void olivec_triangle3uv_bilinear(Olivec_Canvas oc, int x1, int y1,
                                           int x2, int y2, int x3, int y3,
                                           float tx1, float ty1, float tx2,
                                           float ty2, float tx3, float ty3,
                                           float z1, float z2, float z3,
                                           Olivec_Canvas texture) {
  int lx, hx, ly, hy;
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          int u3 = det - u1 - u2;
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
          float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

          float texture_x = tx / z * texture.width;
          if (texture_x < 0)
            texture_x = 0;
          if (texture_x >= (float)texture.width)
            texture_x = texture.width - 1;

          float texture_y = ty / z * texture.height;
          if (texture_y < 0)
            texture_y = 0;
          if (texture_y >= (float)texture.height)
            texture_y = texture.height - 1;

          int precision = 100;
          OLIVEC_PIXEL(oc, x, y) = olivec_pixel_bilinear(
              texture, texture_x * precision, texture_y * precision, precision,
              precision);
        }
      }
    }
  }
}
