#ifndef EFFUX_SKY_HPP
	#define EFFUX_SKY_HPP

	#include "color.hpp"

	// Create earthly or planetary sky parallax background

	class Cloud {
		unsigned short cloudiness;
		Color color;
		unsigned short width;
		unsigned short height;
		short wind_x;
		short wind_y;
		void roll();	// Roll previous clouds, generate new clouds according to cloudiness
	};

	class Sun {
		Color color;
	};

	class Sky {
		unsigned short time;	// stars at nigh, sun at day
		Color color;
		unsigned char layers;
	};

#endif // EFFUX_SKY_HPP
