/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a Tetris style game.
*/

/*
TODO:
- High scores for different bucket and block sizes
- 2 player mode
- Computer player
- Don't rotate block if it would have to go trough other block
- Title screen where moving blocks form the word "Tetrex"
*/

#ifndef TETREX_HPP
	#define TETREX_HPP

	#include <vector>
	#include "program.hpp"

	class Block {
		unsigned char width, height;	// in squares
		//boolean squares[][];			// array of block shape
	};

	class Bucket {
		// This is space where the block fall
		unsigned char with, height;		// in squares
		//boolean squares[][];			// array of block shape
		std::vector<Block> block_collection;	// All different shapes
		void generate_shapes();			// create every kind of block for given width and height
		void check_fills();
		void bomb();					// create a hole with bomb
		void make_block();
		void execute();					// check full lines, drop block down
	};

	class Player {
		unsigned int score;
	};

	class Gameplay {
		Bucket bucket[2];	// two buckets if two players
		//Player[2] player;
	};

	struct highscore {
		std::string name;
		unsigned int score;
	};

	class Halloffame {
		public:
			std::vector<highscore> board;
			bool load();
			bool save();
	};

	class Tetrex : public Program {
		public:
			highscore scoreboard[10];	// TODO: separate scoreboards to different blocks and buckets
			Tetrex();
			~Tetrex();
			bool init_titlescreen();
			bool deinit_titlescreen();
			bool init_gameplay();
			bool deinit_gameplay();
			bool init() override;
			bool mainloop() override;
	};

#endif // TETREX_HPP
