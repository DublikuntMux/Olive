#include "olive/base/tringle.h"
#include "olive/base/color.h"
#include "olive/base/sprite.h"
#include "olive/olive.h"
#include <stdint.h>

/**
 * @brief Normalize a triangle to a bounding box. This is useful for determining
 * the size of a rectangle that is used to draw an image.
 * @param width The width of the image. This is the number of pixels in the
 * image.
 * @param height The height of the image. This is the number of pixels in the
 * image.
 * @param x1 The first corner of the upper left corner of the rectangle.
 * @param y1 The first corner of the upper left corner of the rectangle.
 * @param x2 The second corner of the upper right corner of the rectangle.
 * @param y2 The second corner of the upper right corner of the rectangle.
 * @param x3 The third corner of the upper right corner of the rectangle.
 * @param y3 The fourth corner of the upper right corner of the rectangle.
 * @param lx The x coordinate of the upper left corner of the rectangle.
 * @param hx The x coordinate of the lower left corner of the rectangle.
 * @param ly The y coordinate of the lower left corner of the rectangle.
 * @param hy The y coordinate of the lower left corner of the rectangle.
 * @return true on success false on failure. Note that the values of lx and hx
 * may be out of bounds
 */
bool olivec_normalize_triangle(size_t width, size_t height, int x1, int y1,
                               int x2, int y2, int x3, int y3, int *lx, int *hx,
                               int *ly, int *hy) {
  *lx = x1;
  *hx = x1;
  // Set the value of lx to x2
  if (*lx > x2)
    *lx = x2;
  // Set the lx to x3.
  if (*lx > x3)
    *lx = x3;
  // Set the horizontal boundary of the matrix.
  if (*hx < x2)
    *hx = x2;
  // Set the horizontal coordinate of the rectangle.
  if (*hx < x3)
    *hx = x3;
  // Set the lx to 0.
  if (*lx < 0)
    *lx = 0;
  // Returns true if the width of the box is less than width.
  if ((size_t)*lx >= width)
    return false;
  ;
  // Returns true if the value is less than or equal to the horizontal axis.
  if (*hx < 0)
    return false;
  ;
  // Horizontally adjust the width of the rectangle.
  if ((size_t)*hx >= width)
    *hx = width - 1;

  *ly = y1;
  *hy = y1;
  // Set the value of ly to y2
  if (*ly > y2)
    *ly = y2;
  // Set the value of ly to y3
  if (*ly > y3)
    *ly = y3;
  // Set the hydrogen of the line.
  if (*hy < y2)
    *hy = y2;
  // Set the hy of the ellipse.
  if (*hy < y3)
    *hy = y3;
  // Set the ly value to 0.
  if (*ly < 0)
    *ly = 0;
  // Returns true if the height is greater than height.
  if ((size_t)*ly >= height)
    return false;
  ;
  // Returns true if hy is negative
  if (*hy < 0)
    return false;
  ;
  // Adjusts the height of the rectangle.
  if ((size_t)*hy >= height)
    *hy = height - 1;

  return true;
}

/**
 * @brief Draw a triangle on the Olivec_Canvas. This is equivalent to drawing a
 * barycentric triangle with the origin at ( x1 y1 ) and ( x2 y2 ) being the top
 * left corner of the triangle.
 * @param oc The canvas to draw on. This must have been set prior to calling
 * this function.
 * @param x1 The x coordinate of the first point of the triangle.
 * @param y1 The y coordinate of the first point of the triangle.
 * @param x2 The x coordinate of the second point of the triangle.
 * @param y2 The y coordinate of the second point of the triangle.
 * @param x3 The x coordinate of the third point of the triangle.
 * @param y3 The y coordinate of the third point of the triangle.
 * @param c1 The color to use for the first point.
 * @param c2 The color to use for the second point.
 * @param c3 The color to use for the third point
 */
void olivec_triangle3c(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                       int y3, uint32_t c1, uint32_t c2, uint32_t c3) {
  int lx, hx, ly, hy;
  // Normalize triangles and barycentric triangles.
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    // blend_color mix_colors3 c1 c2 c3 u1 c2 c3 u2 det
    for (int y = ly; y <= hy; ++y) {
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        // blend color of the barycentric color
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          olivec_blend_color(&OLIVEC_PIXEL(oc, x, y),
                             mix_colors3(c1, c2, c3, u1, u2, det));
        }
      }
    }
  }
}

/**
 * @brief Draw a triangle on the Olivec_Canvas. This is equivalent to the OpenGL
 * glTriangle function but the coordinates are normalized to lie in the range [
 * 0 1 ]
 * @param oc The canvas to draw on.
 * @param x1 The x coordinate of the first vertex.
 * @param y1 The y coordinate of the first vertex.
 * @param x2 The x coordinate of the second vertex.
 * @param y2 The y coordinate of the second vertex.
 * @param x3 The x coordinate of the third vertex.
 * @param y3 The y coordinate of the third vertex.
 * @param z1 The z coordinate of the first vertex.
 * @param z2 The z coordinate of the second vertex.
 * @param z3 The z coordinate of the third vertex. Note that this will be
 * ignored if the triangle is parallel
 */
void olivec_triangle3z(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                       int y3, float z1, float z2, float z3) {
  int lx, hx, ly, hy;
  // Normalize triangle of the triangle.
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    for (int y = ly; y <= hy; ++y) {
      // Find the pixel values of the barycentric plane.
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        // The barycentric plane of the barycentric plane.
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          OLIVEC_PIXEL(oc, x, y) = *(uint32_t *)&z;
        }
      }
    }
  }
}

/**
 * @brief Draw a 3 - by - 3 UV triangular section. This is equivalent to the
 * barycentric triangle but with the addition of texture coordinates.
 * @param oc The canvas to draw on. This is ignored if the function is called
 * from outside.
 * @param x1 The x coordinate of the first vertex.
 * @param y1 The y coordinate of the first vertex.
 * @param x2 The x coordinate of the second vertex.
 * @param y2 The y coordinate of the second vertex.
 * @param x3 The x coordinate of the third vertex.
 * @param y3
 * @param tx1
 * @param ty1 The type of texture in the first vertex.
 * @param tx2 The type of texture in the second vertex.
 * @param ty2 The type of texture in the second vertex.
 * @param tx3 The type of texture in the third vertex.
 * @param ty3 The type of texture in the third vertex.
 * @param z1 The first vertex's z coordinate.
 * @param z2 The second vertex's z coordinate.
 * @param z3 The third vertex's z coordinate.
 * @param texture The texture to use for drawing the triangle
 */
void olivec_triangle3uv(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                        int x3, int y3, float tx1, float ty1, float tx2,
                        float ty2, float tx3, float ty3, float z1, float z2,
                        float z3, Olivec_Canvas texture) {
  int lx, hx, ly, hy;
  // Normalize triangle of the triangle.
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    // Find the texture of the bounding box.
    for (int y = ly; y <= hy; ++y) {
      // Find the texture of the barycentric coordinates of the bounding box.
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        // Returns the texture of the barycentric plane.
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          int u3 = det - u1 - u2;
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
          float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

          int texture_x = tx / z * texture.width;
          // Set texture x coordinate to 0
          if (texture_x < 0)
            texture_x = 0;
          // if texture_x is greater than texture. width
          if ((size_t)texture_x >= texture.width)
            texture_x = texture.width - 1;

          int texture_y = ty / z * texture.height;
          // Set texture y coordinate to 0
          if (texture_y < 0)
            texture_y = 0;
          // Set texture y coordinate to the texture height
          if ((size_t)texture_y >= texture.height)
            texture_y = texture.height - 1;
          OLIVEC_PIXEL(oc, x, y) =
              OLIVEC_PIXEL(texture, (int)texture_x, (int)texture_y);
        }
      }
    }
  }
}

/**
 * @brief Draw a bilinear triangle on the Olivec_Canvas. The triangle is defined
 * by the 3uv version of the triangle with the origin at ( x1 y1 ) and ( x2 y2 )
 * being the upper left corner of the triangle and the origin at ( x3 y3 ) being
 * the lower right corner of the triangle.
 * @param oc The canvas to draw on. This is modified by this function.
 * @param x1 The x coordinate of the first vertex.
 * @param y1 The y coordinate of the first vertex.
 * @param x2 The x coordinate of the second vertex.
 * @param y2 The y coordinate of the second vertex.
 * @param x3 The x coordinate of the third vertex.
 * @param y3
 * @param tx1
 * @param ty1 The ty1 of the first vertex.
 * @param tx2 The tx2 of the second vertex.
 * @param ty2 The ty2 of the second vertex.
 * @param tx3 The tx3 of the second vertex.
 * @param ty3 The ty3 of the second vertex.
 * @param z1 The z coordinate of the first vertex.
 * @param z2 The z coordinate of the second vertex.
 * @param z3 The z coordinate of the third vertex.
 * @param texture The texture to use for drawing the triangle
 */
void olivec_triangle3uv_bilinear(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, float tx1, float ty1,
                                 float tx2, float ty2, float tx3, float ty3,
                                 float z1, float z2, float z3,
                                 Olivec_Canvas texture) {
  int lx, hx, ly, hy;
  // Normalize triangle of the triangle.
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    // Computes the pixel values of the OLIVEC texture.
    for (int y = ly; y <= hy; ++y) {
      // Find the pixel values of the bilinear area of the texture.
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        // Returns the pixel value of the bilinear texture.
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          int u3 = det - u1 - u2;
          float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
          float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
          float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

          float texture_x = tx / z * texture.width;
          // Set texture x coordinate to 0
          if (texture_x < 0)
            texture_x = 0;
          // Set texture x coordinate to the texture width
          if (texture_x >= (float)texture.width)
            texture_x = texture.width - 1;

          float texture_y = ty / z * texture.height;
          // Set texture y coordinate to 0
          if (texture_y < 0)
            texture_y = 0;
          // Set texture y coordinate to the texture height
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
