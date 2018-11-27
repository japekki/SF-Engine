#ifndef COLOR_HPP
	#define COLOR_HPP

	#include "types.hpp"

	// TODO:
	// - Optimize: Use only certain color format(s), do not always store and convert everything to everything

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
