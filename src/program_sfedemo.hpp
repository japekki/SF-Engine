/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a demo.
	Merely a collection / showcase / test suite of SF Engine features.
*/

#ifndef PROGRAM_SFEDEMO_HPP
	#define PROGRAM_SFEDEMO_HPP

	#include "program.hpp"

	class SFEdemo : public Program {
		private:
			//EffuxCircles *effux_circles;
			//EffuxTextscroller *effux_textscroller;
		public:
			SFEdemo();
			~SFEdemo();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_SFEDEMO_HPP
