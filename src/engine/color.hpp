// TODO:
// - Optimize;
//		- 4 different color formats:
//			- 0xffffffff
//			- 0xff, 0xff, 0xff, 0xff
//			- {0xff, 0xff, 0xff, 0xff}
//			- 1.0, 1.0, 1.0, 1.0
//		- different color depths (currently only 32 bpp is supported)

#ifndef COLOR_HPP
	#define COLOR_HPP

	#include <SDL.h>

	// COLORS:
		//#define SDL_COLOR_GREEN {0x30, 0xa0, 0x60}

		//#define COLOR_INDIGO 0x303070
		//#define SDLCOLOR_INDIGO {0x30, 0x30, 0x70}
		#define COLOR_INDIGO 0x202060
		#define SDLCOLOR_INDIGO {0x20, 0x20, 0x60}

		#define COLOR_GREEN1 0x207040
		#define SDLCOLOR_GREEN1 {0x20, 0x70, 0x40}

		//#define COLOR_CRTGREEN 0xd0f0d0
		//#define SDLCOLOR_CRTGREEN {0xd0, 0xf0, 0xd0}

		#define COLOR_CRTBLUE 0x204070
		#define SDLCOLOR_CRTBLUE {0x20, 0x40, 0x70}

		#define COLOR_GOLD 0x606010
		#define SDLCOLOR_GOLD {0x60, 0x60, 0x10}

		#define COLOR_RED 0xff0000
		#define SDLCOLOR_RED {0xff, 0, 0}

		#define COLOR_CRTRED 0x702020
		#define SDLCOLOR_CRTRED {0x70, 0x20, 0x20}

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
			float r, g, b;		// red, green, blue
			float h, s, l;		// hue, saturation, lightness
			uint32_t rgbint;	// 32 bpp pixel color
		public:
			Color();
			ColorRGB hsl_to_rgb();
			uint32_t hsl_to_int();
			ColorHSL rgb_to_hsl();
			uint32_t rgb_to_int();
			ColorRGB int_to_rgb();
			ColorHSL int_to_hsl();
			// void blend(Color* color);
			// void invert();
	};

	namespace color {
		SDL_Color UintToSDLColor(uint32_t color);
	};

	//void generate_hsl_table(SDL_Surface *sdlsurface);

#endif // COLOR_HPP
