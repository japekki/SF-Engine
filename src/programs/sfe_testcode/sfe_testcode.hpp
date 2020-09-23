/*
	SF-Engine

	This file has demo/game specific routines.

	This one is a benchmark / test program.
	It is not meant to compare different hardware/drivers, but to help optimize SF Engine routines.
*/

/*
TODO:
- Give test parameter either in loopcount or in time
- Windowed and windowless (renderer only) mode
*/

#ifndef SFE_TESTCODE_HPP
	#define SFE_TESTCODE_HPP

	#include "program.hpp"

	class SFE_Testcode : public Program {
		public:
			SFE_Testcode(int argc, char** argv);
			~SFE_Testcode();
			bool init() override;
			bool mainloop() override;
	};

#endif // SFE_TESTCODE_HPP
