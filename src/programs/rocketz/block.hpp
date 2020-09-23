#ifndef BLOCK_HPP
	#define BLOCK_HPP

	#include <SDL.h>

	// Colors for level blocks:
		#define COLOR_VACUUM		0
		#define COLOR_LAND_GRASS	0x104808
		#define COLOR_LAND_ROCK		0x301c08
		#define COLOR_LAND_SAND		0x646040
		#define COLOR_AIR			0x144888
		#define COLOR_WATER			0x0f1a98
		// TODO: block type into alpha so color can be anything:
			#define BLOCK_VACUUM		0
			#define BLOCK_LAND_GRASS	1
			#define BLOCK_LAND_ROCK		2
			#define BLOCK_LAND_SAND		3
			#define BLOCK_AIR			4
			#define BLOCK_WATER			5

	class Block {
		public:
			// bool meltable, steamable/vaporable, smokable, makes_gas
			bool soft;
			bool sticky;
			uint16_t friction;
			uint16_t burning;	// burning intensity, 0 = no burning
			short flammability;
			uint16_t gas;	// amount of gas to produce when burning
			// If land is hard, it makes damage on impact and leaves a hole when blasted
			// If land is soft, it doesn't make damage on impact and falls straight down without leaving a hole when blasted
			short temperature;	// minus if cold, plus if hot
			SDL_Color color;
			//void execute();
	};

	class Air : public Block {
	};

	class Vacuum : public Block {
	};

	class Land : public Block {
	};

	class Bubblegum : public Land {
		Bubblegum();
	};

	class Ice : public Land {
		Ice();
	};

	class Napalm : public Block {
		Napalm();
	};

	class Snow : public Land {
		Snow();
	};

	class Rock : public Block {
	};

	class Water : public Block {
		public:
			Water();
			void execute();
	};

	class Oil : public Water {
		Oil();
	};

	class Lava : public Land {
		Lava();
	};

#endif // BLOCK_HPP
