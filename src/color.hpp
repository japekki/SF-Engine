// TODO:
// - Optimize: Use only certain color format(s), do not always store and convert everything to everything

#ifndef COLOR_HPP
	#define COLOR_HPP

	#include "types.hpp"

	// COLORS:
		//#define SDL_COLOR_GREEN {0x30, 0xa0, 0x60}

		//#define COLOR_INDIGO 0x303070
		//#define SDLCOLOR_INDIGO {0x30, 0x30, 0x70}
		#define COLOR_INDIGO 0x202060
		#define SDLCOLOR_INDIGO {0x20, 0x20, 0x60}

		#define COLOR_CRTGREEN 0x207040
		#define SDLCOLOR_CRTGREEN {0x20, 0x70, 0x40}

		#define COLOR_GOLD 0x606010
		#define SDLCOLOR_GOLD {0x60, 0x60, 0x10}

		#define COLOR_RED 0xff0000
		#define SDLCOLOR_RED {0xff, 0, 0}

		#define COLOR_GREEN 0x00ff00
		#define SDLCOLOR_GREEN {0, 0xff, 0}

		#define COLOR_BLUE 0x0000ff
		#define SDLCOLOR_BLUE {0, 0, 0xff}

		#define COLOR_WHITE 0xffffff
		#define SDLCOLOR_WHITE {0xff, 0xff, 0xff}

		#define COLOR_BLACK 0
		#define SDLCOLOR_BLACK {0, 0, 0}

		#define COLOR_YELLOW 0xffff00
		#define SDLCOLOR_YELLOW {0xff, 0xff, 0}

		#define COLOR_CYAN 0x00ffff
		#define SDLCOLOR_CYAN {0, 0xff, 0xff}

		#define COLOR_ORANGE 0xff7f00
		#define SDLCOLOR_ORANGE {0xff, 0x7f, 0}

		#define COLOR_VIOLET 0xff00ff
		#define SDLCOLOR_VIOLET {0xff, 0, 0xff}

		//#define COLOR_BROWN {164, 101, 38}
		#define SDLCOLOR_BROWN {164, 101, 38}

		#define COLOR_GREY 0x7f7f7f
		#define SDLCOLOR_GREY {0x7f, 0x7f, 0x7f}

	struct ColorRGB {
		float r;
		float g;
		float b;
	};

	struct ColorHSL {
		float h;
		float s;
		float l;
	};

	class Color {
		private:
			float r, g, b;	// red, green, blue
			float h, s, l;	// hue, saturation, lightness
			unsigned int rgbint;	// 32 bpp pixel color
		public:
			Color();
			ColorRGB hsl_to_rgb();
			unsigned int hsl_to_int();
			ColorHSL rgb_to_hsl();
			unsigned int rgb_to_int();
			ColorRGB int_to_rgb();
			ColorHSL int_to_hsl();
			// void blend(Color* color);
			// void invert();
	};

	//void generate_hsl_table(SDL_Surface *sdlsurface);

#endif // COLOR_HPP
