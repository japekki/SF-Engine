/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a screensaver.
*/

/*
TODO:
- Screensaver settings dialog
- Omit separate console window on MS-Windows
*/

#ifndef PUBLIIPPARI_HPP
	#define PUBLIIPPARI_HPP

	#include <vector>
	#include "program.hpp"
	#include "grapher.hpp"

	// Forward declarations:
		//

	class Faucet {
		public:
			Faucet();
			~Faucet();
			void drip();	// Drip down beer
			void plumps();	// wave beer surface and play sound
			Simplesprite texture;
	};

	class PubLiippari : public Program {
		public:
			Faucet faucet;
			Simplesprite logo;
			std::vector<Simplesprite*> fishes;
			PubLiippari(int argc, char** argv);
			~PubLiippari();
			bool init() override;
			bool mainloop() override;
	};

#endif // PUBLIIPPARI_HPP
