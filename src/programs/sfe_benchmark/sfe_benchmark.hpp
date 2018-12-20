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

#ifndef SFE_BENCHMARK_HPP
	#define SFE_BENCHMARK_HPP

	#include "program.hpp"

	struct benchmark_result {
		unsigned int loopcount;
		unsigned int time;
	};

	class SFE_Benchmark : public Program {
		public:
			SFE_Benchmark();
			~SFE_Benchmark();
			bool init() override;
			bool mainloop() override;
			benchmark_result measure_color(unsigned int loopcount);
			benchmark_result measure_pixeldraw(unsigned int loopcount);
			benchmark_result measure_linedraw(unsigned int loopcount);
			benchmark_result measure_squaredraw(unsigned int loopcount);
			benchmark_result measure_texturedraw(unsigned int loopcount);
			benchmark_result measure_triangledraw(unsigned int loopcount);
			//benchmark_result measure_effux(Uint32 loopcount);
	};

#endif // SFE_BENCHMARK_HPP
