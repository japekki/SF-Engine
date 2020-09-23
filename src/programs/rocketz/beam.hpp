// TODO:
// - different kind of beams (speed, reflectivity)

#ifndef BEAM_HPP
	#define BEAM_HPP

	#include "gamespace.hpp"

	// Forward declarations:
		class Gameplay;

	class Beam : public Gameblob {
		public:
			Beam(Gameplay* gameplay);
			~Beam();
			void draw();
	};

#endif // BEAM_HPP
