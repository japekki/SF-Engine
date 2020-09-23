#ifndef PARTICLE_HPP
	#define PARTICLE_HPP

	#include "space.hpp"

	class Particle : public Blob {
		public:
			uint32_t color1, color2;
			uint16_t intensity;
			//short aging_speed = 1;
			//int time_left = 100;	// Delete particle when timeleft drops to zero
			//int age();
	};

#endif // PARTICLE_HPP
