#ifndef OLIVE_FONT_H
#define OLIVE_FONT_H

#include "types.h"

#define OLIVE_DEFAULT_FONT_HEIGHT 6
#define OLIVE_DEFAULT_FONT_WIDTH 6

char olive_default_glyphs[128][OLIVE_DEFAULT_FONT_HEIGHT][OLIVE_DEFAULT_FONT_WIDTH] = {
	['a'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['b'] = {
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 0, 0 },
	},
	['c'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['d'] = {
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['e'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['f'] = {
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
	},
	['g'] = {
			{ 0, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['h'] = {
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
	},
	['i'] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['j'] = {
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['k'] = {
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 1, 0, 1, 0 },
	},
	['l'] = {
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['m'] = {
			{ 1, 1, 0, 1, 0 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['n'] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['o'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['p'] = {
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
	},
	['q'] = {
			{ 0, 1, 1, 0, 1 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
	},
	['r'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 1, 1, 0 },
			{ 1, 1, 0, 0, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
	},
	['s'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['t'] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
	},
	['u'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 1 },
			{ 0, 1, 0, 0, 1 },
			{ 0, 1, 0, 0, 1 },
			{ 0, 1, 0, 0, 1 },
			{ 0, 0, 1, 1, 1 },
	},
	['v'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['w'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 0, 1, 1, 1, 1 },
	},
	['x'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
	},
	['y'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['z'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
	},

	['A'] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['B'] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['C'] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
	},
	['D'] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['E'] = {
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
	},
	['F'] = {
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
	},
	['G'] = {
			{ 0, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
	},
	['H'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['I'] = {
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['J'] = {
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['K'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['L'] = {
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
	},
	['M'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 0, 1, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['N'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['O'] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
	},
	['P'] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
	},
	['Q'] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 1 },
	},
	['R'] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
	},
	['S'] = {
			{ 0, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
	},
	['T'] = {
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['U'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
	},
	['V'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['W'] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 0, 1, 0, 1, 0 },
	},
	['X'] = {
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
	},
	['Y'] = {
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['Z'] = {
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
	},

	['0'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['1'] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
	},
	['2'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
	},
	['3'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['4'] = {
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
	},
	['5'] = {
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['6'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['7'] = {
			{ 1, 1, 1, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
	},
	['8'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },

	},
	['9'] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 1, 0, 0 },
	},

	[','] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['.'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['-'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
	},
	[':'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	[';'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['['] = {
			{ 1, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 0, 0 },
	},
	[']'] = {
			{ 0, 0, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 1, 1, 1 },
	},
	['('] = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	[')'] = {
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 1, 1, 0 },
	},
	['{'] = {
			{ 0, 1, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
	},
	['}'] = {
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 1, 0 },
	},
	['$'] = {
			{ 0, 0, 1, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 1, 0, 0 },
	},
	['#'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 1, 0, 1, 0 },
	},
	['@'] = {
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1 },
			{ 1, 0, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
	},
	['!'] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['?'] = {
			{ 0, 1, 1, 1, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
	},
	['%'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
	},
	['"'] = {
			{ 0, 1, 0, 0, 1 },
			{ 0, 1, 0, 0, 1 },
			{ 1, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
	},
	['\''] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
	},
	['/'] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
	},
	['\\'] = {
			{ 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 1 },
	},
};

Olive_Font olive_default_font = {
	.glyphs = &olive_default_glyphs[0][0][0],
	.width = OLIVE_DEFAULT_FONT_HEIGHT,
	.height = OLIVE_DEFAULT_FONT_WIDTH,
};

#endif // OLIVE_FONT_H
