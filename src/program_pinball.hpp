#ifndef PROGRAM_PINBALL_HPP
	#define PROGRAM_PINBALL_HPP

	#include "program.hpp"
	#include "projectile.hpp"

	// FILE NAMES:
		#define DATAPATH "../data/"

		// Pictures:
			//#define FILENAME_PIC1 DATAPATH "picture.png"

		// Sounds:
			#define FILENAME_MUSIC_LEVEL1 DATAPATH "kummitustalo.ogg"
			#define FILENAME_SOUND_FLIPPER DATAPATH "flipper.wav"
			#define FILENAME_SOUND_BUMBER1 DATAPATH "bumper1.wav"
			#define FILENAME_SOUND_BUMBER2 DATAPATH "bumper2.wav"
			#define FILENAME_SOUND_MULTIBALL DATAPATH "multiball.wav"
			#define FILENAME_SOUND_EXTRABALL DATAPATH "extraball.wav"
			#define FILENAME_SOUND_DRAIN DATAPATH "drain.wav"
			#define FILENAME_SOUND_HIGHSCORE DATAPATH "highscore.wav"
			#define FILENAME_SOUND_HIT1 DATAPATH "hit1.wav"
			#define FILENAME_SOUND_HIT2 DATAPATH "hit2.wav"
			#define FILENAME_SOUND_HIT3 DATAPATH "hit3.wav"
			#define FILENAME_SOUND_HIT4 DATAPATH "hit4.wav"
			#define FILENAME_SOUND_PUSH DATAPATH "push.wav"
			#define FILENAME_SOUND_TILT DATAPATH "tilt.wav"
			#define FILENAME_SOUND_JACKPOT DATAPATH "jackpot.wav"
			#define FILENAME_SOUND_GAMEOVER DATAPATH "gameover.wav"
			#define FILENAME_SOUND_LAUNCH DATAPATH "launch.wav"
			#define FILENAME_SOUND_RAMP1 DATAPATH "ramp1.wav"
			#define FILENAME_SOUND_RAMP2 DATAPATH "ramp2.wav"

	/*
		Texts in LCD:
			Winners don't use drugs.
			Launch...
			JACKPOT!
			TILT!
	*/

	class LcdPixel {
	};

	class Lcd {
		// LcdPixel[]
	};

	class Bumber {
	};

	class Flipper {
	};

	class Ball : public Projectile2D {
	};

	class Player {
		unsigned int score = 0;
		unsigned short balls_left = 5;	// balls left to launch
	};

	class Level {
		//
	};

	class Level_Halloween : public Level {
	};

	class Gameplay {
		std::vector<Player> players;
		std::vector<Ball> balls;	// balls moving on screen (many balls simultaneously if in multiball mode)
		bool gameover = false;
		void run();
	};

	class Pinball : public Program {
		public:
			Pinball();
			~Pinball();
			bool init() override;
			bool mainloop() override;
			// DATA:
				Mix_Music *music_title;
				SDL_Surface *pic_titlescreen;
	};

#endif // PROGRAM_PINBALL_HPP
