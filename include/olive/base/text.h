#ifndef OLIVE_TEXT_H
#define OLIVE_TEXT_H

#include "olive/types.h"
#include <stddef.h>
#include <stdint.h>

void olive_text(Olive_Canvas oc, const char *text, int tx, int ty, Olive_Font font, size_t glyph_size, uint32_t color);

Olive_Font olive_loadfont_frombuff(unsigned char *buffer, int w, int h, int channels, int glyph_w, int glyph_h, char offset);

void olivec_loadfont_free(Olive_Font font);

#endif // OLIVE_TEXT_H
