#ifndef SMOKE_HPP
	#define SMOKE_HPP

	#include <vector>

	class Particle {
	};

	class Smoke {
		unsigned int color1, color2;
		unsigned short intensity;
		unsigned short fading_speed;
		std::vector<Particle> particles;
	};

#endif // SMOKE_HPP
