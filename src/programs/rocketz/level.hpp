/*
TODO:
- Level editor
- Level file format
- If volcanoes, lava etc. are on a background layer, they're not dangerous
*/

#ifndef LEVEL_HPP
	#define LEVEL_HPP

	#include "gamespace.hpp"

	// Forward declarations:
		class Human;
		class Gameplay;
		class Layer;

	class Volcano {
		// Spills out lava slowly, may erupt and spill a lot of lava into the sky
		// Generates smoke
		uint16_t lava_intensity;
		uint16_t erupt_intensity;
	};

	class Shark : public Gameblob {
		// Eats swimming humans
		uint8_t hungryness;
		void eat(Human* human);
	};

	class Weather {
		public:
			Vector wind_speed;
			short temperature = 0;		// minus for more ice/snow, plus for more lava
			uint8_t rain_amount = 0;
	};

	class Level : public Weather {
		private:
			uint16_t width = 0;
			uint16_t height = 0;
			uint32_t* blocks = nullptr;
			//uint32_t* blocks_new = nullptr;		// Do no alter original block data until whole array has been iterated trough
			void execute_blobs();
			void execute_blocks();
		public:
			Gameplay* gameplay = nullptr;

			uint32_t blockcount = 0;		// size of block pixel array
			SDL_Texture* block_texture = nullptr;	// block_pixels is drawn here

			// Parameters for level:
				int random_seed = 0;
				bool with_blocks = false;
				uint16_t odds_item = 0;
				uint16_t odds_water = 0;
				uint16_t odds_land = 0;
				uint16_t odds_blackhole = 0;
				uint16_t odds_pipe = 0;
				uint16_t odds_volcano = 0;
				uint16_t odds_shark = 0;
				uint16_t scatterness = 0;		// lower number means bigger areas of same block type

				// TODO: Balance parameter(s) for block odds (like: little water and much land)
				uint16_t odds_newitem = 500;	// max frames between new item, minimum is 1
				uint16_t odds_debree = 5;
				std::vector<Layer*> layers;	// Parallax backgrounds
				std::vector<Volcano*> volcanoes;
				std::vector<Shark*> sharks;
				std::vector<Blackhole*> blackholes;

			uint16_t get_width();
			uint16_t get_height();
			void set_size(uint16_t width, uint16_t height);
			void set_block(uint16_t x, uint16_t y, uint32_t block);
			void execute();
			Level(Gameplay* gameplay, uint16_t width, uint16_t height, bool with_blocks);
			~Level();
			void add_layer(Layer *layer);
			void randomize();
	};

#endif // LEVEL_HPP
