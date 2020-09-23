#include "level.hpp"
#include "gameplay.hpp"
#include "block.hpp"

Level::Level(Gameplay* gameplay, uint16_t width, uint16_t height, bool with_blocks) {
	this->gameplay = gameplay;
	this->with_blocks = with_blocks;
	this->set_size(width, height);
}

Level::~Level() {
	if (blocks != nullptr)
		delete blocks;
	if (block_texture != nullptr)
		SDL_DestroyTexture(block_texture);
}

uint16_t Level::get_width() {
	return this->width;
}

uint16_t Level::get_height() {
	return this->width;
}

void Level::add_layer(Layer *layer) {
	layers.push_back(layer);
}

void Level::set_size(uint16_t width, uint16_t height) {
	this->width = width;
	this->height = height;
	if (with_blocks) {
		blockcount = width*height;
		////blockcount = sizeof(blocks) / sizeof(blocks[0]);
			if (blocks != nullptr)
				delete blocks;
			blocks = new uint32_t[width * height];
			//blocks_new = new uint32_t[width * height];
		if (block_texture != nullptr)
			SDL_DestroyTexture(block_texture);
		block_texture = SDL_CreateTexture(gameplay->display->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	}
}

void Level::set_block(uint16_t x, uint16_t y, uint32_t block) {
	if (with_blocks) {
		int index = width * y + x;
		if (index < blockcount)
			blocks[index] = block;
	}
}

void Level::randomize() {
	// TODO:
	// - randomize game objective
	// - randomize size
	// - option to randomize only some parameters

	// Randomize parameters:
		//odds_water = rand() % 1000;
		//odds_land = rand() % 1000;
		//odds_blackhole = rand() % 1000;
		//odds_pipe = rand() % 1000;
		//odds_volcano = rand() % 1000;
		//scatterness = rand() % 1000;
		//odds_newitem  = rand() % 1000;
		//temperature = rand() % 1000;	// minus for more ice/snow, plus for more lava

	with_blocks = rand() % 2;

	if (with_blocks) {
		gameplay->gamespace->collision_type = COLLISION_TYPE_NORMAL;
		// CREATE BLOCKS:
			const uint32_t blocktypes[] = {
				COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR,
				COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR,
				COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR, COLOR_AIR,
				COLOR_AIR, COLOR_AIR, COLOR_LAND_SAND, COLOR_LAND_GRASS, COLOR_LAND_ROCK};
			//for (uint32_t i=0; i<blockcount; i++) {
			//	blocks[i] = blocktypes[rand() % 5];
			//}

			int blocktypeamount = 20;	// sizeof blocktypes
			for (uint16_t x=0; x<width; x++) {
				for (uint16_t y=0; y<height; y++) {
					uint32_t index = uint32_t(float(blocktypeamount) / height * y);
					blocks[y*width + x] = blocktypes[index];
				}
			}
	} else {
		//gameplay->gamespace->collision_type = COLLISION_TYPE_NONE;
		gameplay->gamespace->collision_type = COLLISION_TYPE_NORMAL;
		// CREATE BLACK HOLES:
			if (rand() % 2)
				blackholes.push_back(new Blackhole());
	}

	// CREATE WEATHER:
		// TODO: Wind

	// CREATE ITEMS:

}

void Level::execute_blobs() {
	for (uint32_t i=0; i<gameplay->gamespace->blobs.size(); i++) {
		int x = gameplay->gamespace->blobs[i]->location.x + width/2;
		int y = gameplay->gamespace->blobs[i]->location.y + height/2;
		int index = y * width + x;
		if (index < blockcount and index >= 0) {
			if (blocks[index] == COLOR_LAND_SAND) {
				if (gameplay->gamespace->blobs[i]->type != GAMEBLOB_TYPE_BULLET and
					gameplay->gamespace->blobs[i]->type != GAMEBLOB_TYPE_BLOCKBULLET) {
						gameplay->gamespace->blobs[i]->heading.i *= 0.8;
						gameplay->gamespace->blobs[i]->heading.j *= 0.8;
				}
			}
			if ((blocks[index] == COLOR_LAND_ROCK or blocks[index] == COLOR_LAND_GRASS)
				and (gameplay->gamespace->blobs[i]->type != GAMEBLOB_TYPE_BULLET and
					gameplay->gamespace->blobs[i]->type != GAMEBLOB_TYPE_BLOCKBULLET)) {
						gameplay->gamespace->blobs[i]->heading.i *= 0.1;
						gameplay->gamespace->blobs[i]->heading.j *= 0.1;
			}
			if (blocks[index] == COLOR_LAND_ROCK or blocks[index] == COLOR_LAND_GRASS or blocks[index] == COLOR_LAND_SAND) {
				switch (gameplay->gamespace->blobs[i]->type) {
					case GAMEBLOB_TYPE_BLOCKBULLET:
					case GAMEBLOB_TYPE_BULLET:
						blocks[index] = COLOR_AIR;
						gameplay->gamespace->blobs[i]->can_expire = true;
						gameplay->gamespace->blobs[i]->expirecounter = 0;
						break;
					default:
						break;
				}
			}
		}
	}
}

void Level::execute_blocks() {
	for (uint32_t i = blockcount; i > 0; i--)
		switch (blocks[i]) {
			case COLOR_AIR:
				break;

			//case COLOR_LAND_GRASS:
			//	break;

			//case COLOR_LAND_ROCK:
			//	break;

			case COLOR_LAND_SAND:
				if (i + width < blockcount) {
					// If air below, land drops and air rises:
					if (blocks[i + width] == COLOR_AIR) {
						blocks[i + width] = blocks[i];
						blocks[i] = COLOR_AIR;
					}
					// If water below, land drops and water rises:
					else if (blocks[i + width] == COLOR_WATER) {
						blocks[i + width] = blocks[i];
						blocks[i] = COLOR_WATER;
					}
				}
				break;

			case COLOR_WATER:
				if (i + width < blockcount and i > 0)	{
					// If air below, water drops and air rises:
					if (blocks[i + width] == COLOR_AIR) {
						blocks[i + width] = COLOR_WATER;
						blocks[i] = COLOR_AIR;
					} else {
						if (rand() % 2) {
							// Check first if right is air, then if left is air:
							if (blocks[i + 1] == COLOR_AIR) {
								blocks[i + 1] = COLOR_WATER;
								blocks[i] = COLOR_AIR;
							}
							//else if (blocks[i - 1] == COLOR_AIR) {
							//	blocks[i - 1] = COLOR_WATER;
							//	blocks[i] = COLOR_AIR;
							//}
						} else {
							// Check first if left is air, then if right is air:
							if (blocks[i - 1] == COLOR_AIR) {
								blocks[i - 1] = COLOR_WATER;
								blocks[i] = COLOR_AIR;
							}
							//else if (blocks[i + 1] == COLOR_AIR) {
							//	blocks[i + 1] = COLOR_WATER;
							//	blocks[i] = COLOR_AIR;
							//}
						}
					}
				}
				break;
			default:
				// Copy color as is:
				//blocks_new[i] = blocks[i];
				break;
		}

	// Make rain:
		if (rain_amount > 0)
			for (uint16_t x = 0; x < width; x++)
				if (rand() % (1024) <= rain_amount)
					blocks[x] = COLOR_WATER;

}

void Level::execute() {
	if (with_blocks) {
		this->execute_blobs();
		this->execute_blocks();
		SDL_UpdateTexture(block_texture, NULL, blocks, this->width * sizeof(uint32_t));
	}
}
