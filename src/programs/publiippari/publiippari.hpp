/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a screensaver.
*/

/*
TODO:
- Screensaver settings dialog
*/

#ifndef PUBLIIPPARI_HPP
	#define PUBLIIPPARI_HPP

	#include <vector>
	#include "program.hpp"
	#include "sprite.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"
		#define FILENAME_LOGO DATAPATH "logo.png"
		//#define FILENAME_KANNIKALA1 DATAPATH "kannikala1.png"
		//#define FILENAME_KANNIKALA2 DATAPATH "kannikala2.png"

	class Faucet {
		public:
			void drip();	// Drip down beer
	};

	class PubLiippari : public Program {
		public:
			Faucet faucet;
			std::vector<Sprite> kannikalat;
			PubLiippari();
			~PubLiippari();
			bool init() override;
			bool mainloop() override;
	};

#endif // PUBLIIPPARI_HPP
