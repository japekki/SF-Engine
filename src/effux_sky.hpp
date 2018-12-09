// Create earthly or planetary sky parallax background

/*
TODO:
- Raining/snowing
- Twilight
- Birds, balloons, airplanes etc.
- Rainbow
- Heat wobble
- Star field
- Movement paths/curves for suns, planets and stars
*/

#ifndef EFFUX_SKY_HPP
	#define EFFUX_SKY_HPP

	#include "color.hpp"
	#include "particle.hpp"

	class Cloud : public Particle {
		unsigned short thickness;
		Color color;
		unsigned short width;
		unsigned short height;
		//short wind_x;
		//short wind_y;
	};

	class Sun {
		Color color;
		unsigned short radius;
		unsigned short glow_amount;
		unsigned char smileyface;	// 0 = no face
		unsigned char ray_amount;	// how many ray lines
		unsigned char ray_width;	// line width
		unsigned char ray_rotation_degree;
		char ray_rotation_speed;	// negative for counter clockwise, positive for clockwise
	};

	class Sky {
		unsigned char layers;	// TODO: Each sky as layer or many layers in one sky?
		unsigned short time;	// stars at nigh, sun at day
		Color color;
		Sun *sun;				// TODO: multiple suns
		unsigned short cloudiness;
		void roll_clouds();		// Roll previous clouds, generate new clouds according to cloudiness
	};

#endif // EFFUX_SKY_HPP
