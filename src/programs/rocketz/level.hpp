/*
TODO:
- Level editor
- Level file format
- If volcanoes, lava etc. are on a background layer, they're not dangerous
*/

#ifndef LEVEL_HPP
	#define LEVEL_HPP

	#include "geom.hpp"
	#include "grapher.hpp"

	// Forward declarations:
	class Land;
	class Human;

	class Effuxlayer : public Layer {
		// effux->execute();	// execute some effux
	};

	class Staticlayer : public Layer {
		bool load();	// load image file
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

	class Shark : public Polygon {
		// Eats swimming humans
		short health;
		unsigned char hungryness;
		void eat(Human* human);
	};

	class Level {
		public:
			Uint32 width, height;
			//Parameters parameters;
			std::vector<Layer*> layers;	// Parallax backgrounds
			//std::vector<Waterpixel> water;
			std::vector<Volcano*> volcanoes;
			std::vector<Shark*> sharks;
			std::vector<Land*> landpixels;
			Level(Uint32 width, Uint32 height);
			~Level();
			void add_layer(Layer *layer);
	};

	class RandomLevel {
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
			RandomLevel(Uint32 width, Uint32 height);
			~RandomLevel();
			void set_size(Uint32 width, Uint32 height);
			void generate();
	};

#endif // LEVEL_HPP
