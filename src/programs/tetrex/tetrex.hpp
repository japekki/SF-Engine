/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a Tetris style game.
*/

/*
TODO:
- High scores for different bucket and block sizes
- Multiplayer mode (2 or even more)
- Computer player
- Don't rotate block if it would have to go trough other block
- Title screen where moving blocks form the word "Tetrex"
*/

#ifndef TETREX_HPP
	#define TETREX_HPP

	#include <vector>
	#include "program.hpp"

	class Piece {
		unsigned char width, height;	// in squares
		//bool squares[][];			// array of block shape
		void create_all_pieces(unsigned char block_count);
		bool rotate_cw();
		bool rotate_ccw();
	};

	class Bucket {
		private:
			std::vector<Piece> block_collection;	// All different shapes
			void generate_shapes();					// create every kind of block for given width and height
			void check_fills();
		public:
			Bucket();
			~Bucket();
			unsigned char width, height;	// in squares
			//boolean squares[][];			// array of block shape
			void bomb();					// create a hole with bomb
			void make_block();
			void execute();					// check full lines, drop block down
	};

	class Player {
		uint32_t score;
	};

	struct highscore {
		std::string name;
		uint32_t score;
	};

	class Halloffame {
		public:
			std::vector<highscore> board;
			bool load();
			bool save();
	};

	class Level {
		public:
			Bucket* bucket;
			highscore hiscore;
			//Bucket bucket[2];	// two buckets if two players
	};

	class Gameplay {
		public:
			Level* level;
			std::vector<Player> players;
			Display* display;
			Audio* audio;
			Gameplay(Display* display, Audio* audio);
			~Gameplay();
	};

	class Tetrex : public Program {
		public:
			const std::string text_title = "Tetrex (yet another Tetris clone)";
			//highscore scoreboard[10];	// TODO: separate scoreboards to different blocks and buckets
			Tetrex(int argc, char** argv);
			~Tetrex();
			Gameplay* gameplay;
			bool init_titlescreen();
			bool deinit_titlescreen();
			bool init_gameplay();
			bool deinit_gameplay();
			bool init() override;
			bool mainloop() override;
	};

#endif // TETREX_HPP
