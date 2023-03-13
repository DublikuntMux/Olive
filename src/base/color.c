#include "olive/base/color.h"
#include "olive/olive.h"
#include <stdint.h>

/**
 * @brief Blend two colors using linear interpolation. This is useful for color
 * blending where you don't know the alpha value of the color but want to make
 * it a good color for your application
 * @param c1 pointer to the first color
 * @param c2 pointer to the second color ( must be normalized
 */
void olivec_blend_color(uint32_t *c1, uint32_t c2) {
  uint32_t r1 = OLIVEC_RED(*c1);
  uint32_t g1 = OLIVEC_GREEN(*c1);
  uint32_t b1 = OLIVEC_BLUE(*c1);
  uint32_t a1 = OLIVEC_ALPHA(*c1);

  uint32_t r2 = OLIVEC_RED(c2);
  uint32_t g2 = OLIVEC_GREEN(c2);
  uint32_t b2 = OLIVEC_BLUE(c2);
  uint32_t a2 = OLIVEC_ALPHA(c2);

  r1 = (r1 * (255 - a2) + r2 * a2) / 255;
  // Set the color to the nearest red color
  if (r1 > 255)
    r1 = 255;
  g1 = (g1 * (255 - a2) + g2 * a2) / 255;
  // Set the g1 to 255.
  if (g1 > 255)
    g1 = 255;
  b1 = (b1 * (255 - a2) + b2 * a2) / 255;
  // Set the value of the color to the nearest 255 to 255.
  if (b1 > 255)
    b1 = 255;

  *c1 = OLIVEC_RGBA(r1, g1, b1, a1);
}

/**
 * @brief Fill the canvas with a color. This is equivalent to drawing a fill -
 * around - the - edges pattern in Olivec.
 * @param oc The canvas to fill. Must have been initialized.
 * @param color The color to fill with. If you don't want to fill the entire
 * canvas use 0
 */
void olivec_fill(Olivec_Canvas oc, uint32_t color) {
  for (size_t y = 0; y < oc.height; ++y) {
    for (size_t x = 0; x < oc.width; ++x) {
      OLIVEC_PIXEL(oc, x, y) = color;
    }
  }
}

/**
 * @brief Mix two colors using a factor u. This is similar to mix_colors but the
 * determinant is used to determine how much of the colors are mixed.
 * @param c1 First color to be mixed. Must be in the range 0 - 255.
 * @param c2 Second color to be mixed. Must be in the range 0 - 255.
 * @param u1 Mixing factor for the first color.
 * @param det Detection factor for the second color. If 0 no determinant is
 * used.
 * @return The result of the mixing. It is a 32 bit uint32_t but can be cast to
 * uint32
 */
uint32_t mix_colors2(uint32_t c1, uint32_t c2, int u1, int det) {
  // TODO: estimate how much overflows are an issue in integer only environment
  int64_t r1 = OLIVEC_RED(c1);
  int64_t g1 = OLIVEC_GREEN(c1);
  int64_t b1 = OLIVEC_BLUE(c1);
  int64_t a1 = OLIVEC_ALPHA(c1);

  int64_t r2 = OLIVEC_RED(c2);
  int64_t g2 = OLIVEC_GREEN(c2);
  int64_t b2 = OLIVEC_BLUE(c2);
  int64_t a2 = OLIVEC_ALPHA(c2);

  // Returns the RGBA value of the detector.
  if (det != 0) {
    int u2 = det - u1;
    int64_t r4 = (r1 * u2 + r2 * u1) / det;
    int64_t g4 = (g1 * u2 + g2 * u1) / det;
    int64_t b4 = (b1 * u2 + b2 * u1) / det;
    int64_t a4 = (a1 * u2 + a2 * u1) / det;

    return OLIVEC_RGBA(r4, g4, b4, a4);
  }

  return 0;
}

/**
 * @brief Mix two colors using 3 different colors. This is similar to mix_colors
 * but the colors are specified as uint32_t rather than uint32_t because of the
 * need to convert them to int64_t before mixing
 * @param c1 First color to be mixed. Should be a 32 bit color. If it's 0 then
 * we don't care about the alpha channel.
 * @param c2 Second color to be mixed. Should be a 32 bit color. If it's 0 then
 * we don't care about the alpha channel.
 * @param c3 Third color to be mixed. Should be a 32 bit color. If it's 0 then
 * we don't care about the alpha channel
 * @param u1 Red component of the first color to be mixed.
 * @param u2 Red component of the second color to be mixed.
 * @param det Detection factor for the colors. 0 = no detection 1 = determinant
 * of colors.
 * @return A 32 bit color that is the result of mixing the colors specified by
 * the arguments. If det is non - zero it will be used to determine the color of
 * the first color
 */
uint32_t mix_colors3(uint32_t c1, uint32_t c2, uint32_t c3, int u1, int u2,
                     int det) {
  // TODO: estimate how much overflows are an issue in integer only environment
  int64_t r1 = OLIVEC_RED(c1);
  int64_t g1 = OLIVEC_GREEN(c1);
  int64_t b1 = OLIVEC_BLUE(c1);
  int64_t a1 = OLIVEC_ALPHA(c1);

  int64_t r2 = OLIVEC_RED(c2);
  int64_t g2 = OLIVEC_GREEN(c2);
  int64_t b2 = OLIVEC_BLUE(c2);
  int64_t a2 = OLIVEC_ALPHA(c2);

  int64_t r3 = OLIVEC_RED(c3);
  int64_t g3 = OLIVEC_GREEN(c3);
  int64_t b3 = OLIVEC_BLUE(c3);
  int64_t a3 = OLIVEC_ALPHA(c3);

  // Returns the RGBA value of the first det in the range 0 1.
  if (det != 0) {
    int u3 = det - u1 - u2;
    int64_t r4 = (r1 * u1 + r2 * u2 + r3 * u3) / det;
    int64_t g4 = (g1 * u1 + g2 * u2 + g3 * u3) / det;
    int64_t b4 = (b1 * u1 + b2 * u2 + b3 * u3) / det;
    int64_t a4 = (a1 * u1 + a2 * u2 + a3 * u3) / det;

    return OLIVEC_RGBA(r4, g4, b4, a4);
  }

  return 0;
}
