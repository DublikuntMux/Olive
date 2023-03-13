#include <olive.h>
#include <stdint.h>

/**
* @brief Create a Olivec_Canvas from a pointer to pixel data. The pixels are converted to 32 - bit integers and stored in a struct that can be used to draw to the screen.
* @param pixels Pointer to the buffer containing the image data.
* @param width The width of the image in pixels. This must be a multiple of 4.
* @param height The height of the image in pixels. This must be a multiple of 4.
* @param stride The distance between scanlines in pixels. This must be a multiple of 4.
* @return An object of type Olivec_Canvas. You must call oc. destroy () when done
*/
Olivec_Canvas olivec_canvas(uint32_t *pixels, size_t width, size_t height,
                            size_t stride) {
  Olivec_Canvas oc = {
      .pixels = pixels,
      .width = width,
      .height = height,
      .stride = stride,
  };
  return oc;
}

/**
* @brief Return a subcanvas that is a copy of the specified canvas. This can be used to create a subcanvas from a rectangular area in the form of a rectangle.
* @param oc The canvas to copy the subcanvas from.
* @param x The x coordinate of the upper - left corner of the rectangle.
* @param y The y coordinate of the upper - left corner of the rectangle.
* @param w The width of the rectangle. If w is negative it is interpreted as the distance from the left edge of the canvas.
* @param h The height of the rectangle. If h is negative it is interpreted as the distance from the top edge of the canvas.
* @return An object of type Olivec_Canvas which has been filled with the subcanvas. If an error occurs OLIVEC_CANVAS_NULL is returned
*/
Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w, int h) {
  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to a rectangular rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return OLIVEC_CANVAS_NULL;
  oc.pixels = &OLIVEC_PIXEL(oc, nr.x1, nr.y1);
  oc.width = nr.x2 - nr.x1 + 1;
  oc.height = nr.y2 - nr.y1 + 1;
  return oc;
}

/**
* @brief Find the barycentric coordinates of a point. This is a version of Olivec's barycentric () function that works with any coordinate system.
* @param x1 x coordinate of first point. ( x1 > = 0 )
* @param y1 y coordinate of first point. ( y1 > = 0 )
* @param x2 x coordinate of second point. ( x2 > = 0 )
* @param y2 y coordinate of second point. ( y2 > = 0 )
* @param x3 x coordinate of point. ( x3 > = 0 )
* @param y3 y coordinate of point. ( x3 > = 0 )
* @param xp x coordinate of point. ( yp > = 0 )
* @param yp y coordinate of point. ( xp > = 0 )
* @param u1 u coordinate of first point. ( x1 - x3 ) * ( yp - yp )
* @param u2 u coordinate of second point. ( x1 - x3 ) * ( yp - yp )
* @param det det of first point. ( int ) This is set to 0 if there is no determinant
* @return true if the point is on
*/
bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3, int y3, int xp,
                        int yp, int *u1, int *u2, int *det) {
  *det = ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3));
  *u1 = ((y2 - y3) * (xp - x3) + (x3 - x2) * (yp - y3));
  *u2 = ((y3 - y1) * (xp - x3) + (x1 - x3) * (yp - y3));
  int u3 = *det - *u1 - *u2;
  return ((OLIVEC_SIGN(int, *u1) == OLIVEC_SIGN(int, *det) || *u1 == 0) &&
          (OLIVEC_SIGN(int, *u2) == OLIVEC_SIGN(int, *det) || *u2 == 0) &&
          (OLIVEC_SIGN(int, u3) == OLIVEC_SIGN(int, *det) || u3 == 0));
}

/**
* @brief Draw text on the canvas. This is a convenience function for drawing text on the Olivec_Canvas.
* @param oc The canvas to draw on. This must be initialized.
* @param text The text to draw. It must be null - terminated.
* @param tx The x - coordinate of the upper - left corner of the text.
* @param ty The y - coordinate of the upper - left corner of the text.
* @param font The font to use for drawing. If NULL the default font is used.
* @param glyph_size The size of each glyph in pixels.
* @param color The color of the text in the form 0xRRGGBB
*/
void olivec_text(Olivec_Canvas oc, const char *text, int tx, int ty,
                 Olivec_Font font, size_t glyph_size, uint32_t color) {
  // Draw all the glyphs in the font.
  for (size_t i = 0; *text; ++i, ++text) {
    int gx = tx + i * font.width * glyph_size;
    int gy = ty;
    const char *glyph =
        &font.glyphs[(*text) * sizeof(char) * font.width * font.height];
    // Draw all glyphs in the font.
    for (int dy = 0; (size_t)dy < font.height; ++dy) {
      // Draw the glyph on the font.
      for (int dx = 0; (size_t)dx < font.width; ++dx) {
        int px = gx + dx * glyph_size;
        int py = gy + dy * glyph_size;
        // Draw the glyph if it is within the font.
        if (0 <= px && px < (int)oc.width && 0 <= py && py < (int)oc.height) {
          // Draw the glyph at the given position.
          if (glyph[dy * font.width + dx]) {
            olivec_rect(oc, px, py, glyph_size, glyph_size, color);
          }
        }
      }
    }
  }
}

/**
* @brief Compute the binomial coefficient of a number. This is used to compute the number of successes and failures in Olivec's test suite.
* @param n the number of trials. Must be greater than or equal to 2.
* @param i the number of successes to compute. Must be greater than or equal to 2.
* @return the binomial coefficient of n trials and failures with probability 1 - i. Note that i is a constant
*/
double olivec_binomial_coeffs(int n, int i) {
  double result = 1;
  // Returns the result of the product of the two points.
  for (int j = 1; j <= i; j++) {
    result *= (n - i + j) / (double)j;
  }
  return result;
}

// TODO: Benchmarking
// TODO: Bezier curves
// TODO: SIMD implementations
// TODO: olivec_ring
// TODO: fuzzer
// TODO: Stencil
