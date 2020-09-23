#include "sfe_benchmark.hpp"
#include <SDL.h>
#include "display.hpp"

SFE_Benchmark::SFE_Benchmark(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "SFE Benchmark";
		version = "0.0001";
}

SFE_Benchmark::~SFE_Benchmark() {
}

benchmark_result SFE_Benchmark::measure_color(uint32_t loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_pixeldraw(uint32_t loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_linedraw(uint32_t loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_squaredraw(uint32_t loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_texturedraw(uint32_t loopcount) {
	// Draw textures of different format to different targets
	uint32_t time_start = SDL_GetTicks();
	// TODO: run tests
	benchmark_result result;
	result.loopcount = loopcount;
	result.time = SDL_GetTicks() - time_start;
	return result;
}

benchmark_result measure_triangledraw() {
	// Draw triangles
	uint32_t time_start = SDL_GetTicks();
	// TODO: run tests
	benchmark_result result;
	//result.loopcount = loopcount;
	result.time = SDL_GetTicks() - time_start;
	return result;
}

bool SFE_Benchmark::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(0);	// Don't limit FPS
		display->resizable_window = false;
		//display->vsync = true;		// False by default, keep it false
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool SFE_Benchmark::mainloop() {
	while (!mainloop_done and this->works) {
		// benchmark/measure something
		get_events();
		display->refresh();
	}
	return this->works;
}
