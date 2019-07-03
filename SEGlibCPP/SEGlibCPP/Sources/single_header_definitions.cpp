/*
	This fine includes all definitions/implementations of single-header libraries
*/
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>

#undef STB_VORBIS_HEADER_ONLY
#include <stb/stb_vorbis.c>

#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#include <nuklear/nuklear.h>