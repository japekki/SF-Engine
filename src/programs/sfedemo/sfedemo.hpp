/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a demo.
	Merely a collection / showcase / test suite of SF Engine features.
*/

#ifndef SFEDEMO_HPP
	#define SFEDEMO_HPP

	#include "program.hpp"
	#include "world.hpp"

	class SFEdemo : public Program {
		private:
			Timeline *timeline;
			//EffuxCircles *effux_circles;
			//EffuxTextscroller *effux_textscroller;
			World world_room;
		public:
			SFEdemo();
			~SFEdemo();
			bool init() override;
			bool world_room_init();
			bool mainloop() override;
	};

#endif // SFEDEMO_HPP
