/*
TODO:
- Level editor
- Level file format
- If volcanoes, lava etc. are on a background layer, they're not dangerous
*/

#ifndef LEVEL_HPP
	#define LEVEL_HPP

	#include "geom.hpp"
	#include "human.hpp"
	#include "land.hpp"

	// LAYER TYPES:
		#define LAYER_NONE 0
		#define LAYER_COLOR 1
		#define LAYER_BITMAP 2
		#define LAYER_EFFUX 3

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_VOLCANO_ERUPT DATAPATH "volcanoerupt.wav"

	class Background {
		unsigned short type = LAYER_NONE;
		//SDL_Texture *bitmap;
		// TODO: pointer for effux
	};

	class Wind {
		short speed;	// minus winds to the left, plus winds to the right
	};

	class Volcano {
		// Spills out lava slowly, may erupt and spill a lot of lava into the sky
		// Generates smoke
		unsigned short lava_intensity;
		unsigned short erupt_intensity;
	};

	class Shark : public Polygon2D {
		// Eats swimming humans
		short lifeforce;
		unsigned char hungryness;
		void eat(Human* human);
	};

	class Level {
		public:
			Uint32 width, height;
			//Parameters parameters;
			std::vector<Background> backgrounds;	// Parallax backgrounds
			//std::vector<Waterpixel> water;
			std::vector<Volcano> volcanoes;
			std::vector<Shark> sharks;
			std::vector<Land> landpixels;
			Level(Uint32 width, Uint32 height);
			~Level();
	};

	class Randomlevelgenerator {
		public:
			Level *level;
			int seed;
			Uint32 width, height;
			Uint32 wateramount;
			Uint32 landamount;
			Uint32 blackholes;
			Uint32 scatterness;
			Uint32 pipe_amount;
			Uint32 volcano_amount;
			int temperature;	// minus for more ice/snow, plus for more lava
			// randomize base locations (players can change it)
			Randomlevelgenerator(Uint32 width, Uint32 height);
			~Randomlevelgenerator();
			void set_size(Uint32 width, Uint32 height);
			void generate();
	};

#endif // LEVEL_HPP
