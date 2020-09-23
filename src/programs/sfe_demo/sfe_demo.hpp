/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a demo.
	Merely a collection / showcase / test suite of SF Engine features.
*/

#ifndef SFE_DEMO_HPP
	#define SFE_DEMO_HPP

	#include "program.hpp"

	// Forward declarations:
		class World;
		class EffuxCircles;
		class EffuxTextscroller;
		class EffuxTwister;
		class Timeline;

	class SFE_Demo : public Program {
		private:
			Timeline *timeline;
			EffuxCircles *effux_circles;
			EffuxTextscroller *effux_scroller_intro;
			EffuxTwister *effux_twister;
			World* world_room;
		public:
			SFE_Demo(int argc, char** argv);
			~SFE_Demo();
			bool init() override;
			bool world_room_init();
			bool mainloop() override;
			const std::string text_intro =
				"SFE Demo\n"
				"By JaPeK";
	};

#endif // SFE_DEMO_HPP
