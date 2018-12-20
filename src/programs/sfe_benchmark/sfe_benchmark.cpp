#include "sfe_benchmark.hpp"
#include <SDL.h>
#include "display.hpp"

SFE_Benchmark::SFE_Benchmark() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "SFE Benchmark";
		this->version = "0.0001";
}

SFE_Benchmark::~SFE_Benchmark() {
}

benchmark_result SFE_Benchmark::measure_color(unsigned int loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_pixeldraw(unsigned int loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_linedraw(unsigned int loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_squaredraw(unsigned int loopcount) {
	benchmark_result result;
	return result;
}

benchmark_result SFE_Benchmark::measure_texturedraw(unsigned int loopcount) {
	// Draw textures of different format to different targets
	Uint32 time_start = SDL_GetTicks();
	// TODO: run tests
	benchmark_result result;
	result.loopcount = loopcount;
	result.time = SDL_GetTicks() - time_start;
	return result;
}

benchmark_result measure_triangledraw() {
	// Draw triangles
	Uint32 time_start = SDL_GetTicks();
	// TODO: run tests
	benchmark_result result;
	//result.loopcount = loopcount;
	result.time = SDL_GetTicks() - time_start;
	return result;
}

bool SFE_Benchmark::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(0);	// Don't limit FPS
		this->display->resizable_window = false;
		//this->display->vsync = true;		// False by default, keep it false
		//this->display->mousecursor_visible = false;
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool SFE_Benchmark::mainloop() {
	while (!this->mainloop_done and this->works) {
		get_events();
		this->display->refresh();
	}
	return this->works;
}
