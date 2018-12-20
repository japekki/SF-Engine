/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a pinball game.
*/

#ifndef PINBALL_HPP
	#define PINBALL_HPP

	#include "program.hpp"
	#include <SDL_mixer.h>
	#include "geom.hpp"
	#include "projectile.hpp"

	// Forward declarations:

	// TODO: LCD FONT

	class LcdPixel {
	};

	class Lcd {
		// LcdPixel[]
		// TODO: blink, scroll horizontally, scroll vertically, twinkle, transition effects
	};

	class Bumber {
	};

	class Flipper : public Polygon {
	};

	class Ball : public Projectile {
	};

	class Player {
		unsigned int score = 0;
		unsigned short balls_left = 5;	// balls left to launch
	};

	class Level {
		/*
		Texts in LCD:
			"Winners don't use drugs."
			"Launch..."
			"paused"
			"That was bad - try again!"
			"JACKPOT!"
			"TILT!"
			"HAPPY HOUR!"
			"HIGHSCORE!"
			"GAME OVER!"
		*/
	};

	class Level_Halloween : public Level {
		/*
		Texts in LCD:
			"TRICK OR TREAT"
			"SPOOOOOKY"
			"HAUNTED"
		*/
	};

	class Level_Robolab : public Level {
		/*
		Texts in LCD:
			"Charging..."
			"Charged up"
			"SUPERCHARGE"
			"Transmission"
			"Firmware updated"
			"Programming complete"
			"All systems activated"
			"IT'S ALIVE!"
			"Reboot"
			"Short circuit"
			"Low battery"
		*/
	};

	class Gameplay {
		public:
			std::vector<Player> players;
			std::vector<Ball> balls_in_play;	// balls moving on screen (many balls simultaneously if in multiball mode)
			Uint8 balls_left;					// Relaunches
			bool gameover = false;
			void run();
	};

	class Pinball : public Program {
		public:
			Pinball();
			~Pinball();
			bool init() override;
			bool mainloop() override;
			Mix_Music *music_title = nullptr;
	};

#endif // PINBALL_HPP
