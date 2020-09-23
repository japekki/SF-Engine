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

/*
TESTS:
- Alpha enabled/disabled
- Pixel formats
*/

#ifndef SFE_BENCHMARK_HPP
	#define SFE_BENCHMARK_HPP

	#include "program.hpp"

	struct benchmark_result {
		uint32_t loopcount = 0;
		uint32_t time = 0;
	};

	class SFE_Benchmark : public Program {
		public:
			SFE_Benchmark(int argc, char** argv);
			~SFE_Benchmark();
			bool init() override;
			bool mainloop() override;
			benchmark_result measure_color(uint32_t loopcount);
			benchmark_result measure_pixeldraw(uint32_t loopcount);
			benchmark_result measure_linedraw(uint32_t loopcount);
			benchmark_result measure_squaredraw(uint32_t loopcount);
			benchmark_result measure_texturedraw(uint32_t loopcount);
			benchmark_result measure_triangledraw(uint32_t loopcount);
			//benchmark_result measure_effux(uint32_t loopcount);
	};

#endif // SFE_BENCHMARK_HPP
