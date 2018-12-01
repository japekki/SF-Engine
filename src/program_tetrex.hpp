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
*/

#ifndef PROGRAM_TETREX_HPP
	#define PROGRAM_TETREX_HPP

	#include "program.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sounds:
		#define FILENAME_SOUND_BLOCKDOWN DATAPATH "blockdown.wav"
		#define FILENAME_SOUND_LINEFULL DATAPATH "linefull.wav"
		#define FILENAME_SOUND_GAMEOVER DATAPATH "gameover.wav"
		#define FILENAME_SOUND_HIGHSCORE DATAPATH "highscore.wav"
		#define FILENAME_SOUND_BOMB DATAPATH "bomb.wav"
		#define FILENAME_SOUND_PAUSE DATAPATH "pause.wav"

	class Block {
		unsigned char width, height;	// in squares
		//boolean squares[][];			// array of block shape
	};

	class Bucket {
		// This is space where the block fall
		unsigned char with, height;		// in squares
		//boolean squares[][];			// array of block shape
		std::vector<Block> block_collection;	// All different shapes
		void generate_shapes();			// Create every kind of block for given width and height
		void check_fills();
	};

	class Tetrex : public Program {
		public:
			Tetrex();
			~Tetrex();
			bool init_titlescreen();
			bool deinit_titlescreen();
			bool init_gameplay();
			bool deinit_gameplay();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_TETREX_HPP
