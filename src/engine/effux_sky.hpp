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

	#include <vector>
	#include "color.hpp"
	#include "particle.hpp"

	class Cloud : public Particle {
		uint16_t thickness;
		Color color;
		uint16_t width;
		uint16_t height;
	};

	class Planet {
	};

	class Sun {
		Color color;
		uint16_t radius;
		uint16_t glow_amount;
		unsigned char smileyface;	// 0 = no face
		unsigned char ray_amount;	// how many ray lines
		unsigned char ray_width;	// line width
		unsigned char ray_rotation_degree;
		char ray_rotation_speed;	// negative for counter clockwise, positive for clockwise
	};

	class Sky {
		uint16_t time;	// stars at nigh, sun at day
		Color color;
		//short wind_x;
		//short wind_y;
		std::vector<Planet*> planets;
		std::vector<Sun*> suns;
		std::vector<Cloud*> clouds;
		uint16_t cloudiness;
		void roll_clouds();		// Roll previous clouds, generate new clouds according to cloudiness
	};

#endif // EFFUX_SKY_HPP
