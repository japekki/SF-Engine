/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a pinball game.
*/

/*
TODO:
	- LCD FONT
*/

#ifndef PINBALL_HPP
	#define PINBALL_HPP

	#include <SDL_ttf.h>
	#include <SDL_mixer.h>
	#include "program.hpp"
	#include "geometry.hpp"
	#include "space.hpp"
	#include "audio.hpp"

	// Forward declarations:
		class Gameplay;

	class Gameblob : public Blob {
		public:
			Gameplay* gameplay;
			Gameblob(Gameplay* gameplay);
			~Gameblob();
			void draw() = 0;
	};

	class LcdPixel {
	};

	class Lcd {
		// LcdPixel[]
		// TODO: blink, scroll horizontally, scroll vertically, twinkle, transition effects
	};

	class Bumper {
	};

	class Flipper {
	};

	class Tube {
	};

	class Trigger {
	};

	class Launcherspring {
	};

	class Ball : public Gameblob {
		public:
			SDL_Texture* sdltexture;
			Ball(Gameplay* gameplay);
			virtual ~Ball();
			void create_texture(uint32_t width, uint32_t height);
			void draw();
	};

	class Player {
		public:
			std::string name;
			uint32_t score = 0;
			uint8_t balls_left = 5;	// balls left to launch
	};

	class Highscore {
		public:
			char* player_name;
			uint32_t player_score;
			std::string filename = "highscore.dat";
			bool load();
			bool save();
	};

	class Level {
		public:
			Gameplay* gameplay;
			std::vector<Highscore> halloffame;
			std::vector<Flipper*> flippers;
			std::vector<Bumper*> bumpers;
			std::vector<Tube*> tubes;
			std::vector<Trigger*> triggers;
			SDL_Texture* background;
			Launcherspring spring;
			Level(Gameplay* gameplay);
			~Level();
			void execute();
			void draw();
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
			Level* level;
			std::vector<Player*> players;
			std::vector<Ball*> balls_in_play;	// balls moving on screen (many balls simultaneously if in multiball mode)
			Display* display;
			Audio* audio;
			Mix_Music *music_gameplay = nullptr;
			// FONTS:
				TTF_Font *font_lcd_huge = nullptr;
			Space* space;
			Gameplay(Display* display, Audio *audio);
			~Gameplay();
			bool gameover = false;
			void run();
	};

	class Pinball : public Program {
		public:
			// FONTS:
				//TTF_Font *font_lcd_huge = nullptr;
			Gameplay* gameplay;
			Pinball(int argc, char** argv);
			~Pinball();
			bool init() override;
			bool mainloop() override;
			Mix_Music *music_title = nullptr;
	};

#endif // PINBALL_HPP
