#include <SDL.h>
#include "misc.hpp"
#include "display.hpp"

// SELECT PROGRAM TO BUILD:
	// TODO: Some better way to make new programs against the engine
	#include "program.hpp"		// Empty program skeleton, included automatically by other program targets
	//#include "programs/sfedemo/sfedemo.hpp"
	//#include "programs/cavebombers/cavebombers.hpp"
	//#include "programs/pinball/pinball.hpp"
	//#include "programs/publiippari/publiippari.hpp"
	//#include "programs/rocketz/rocketz.hpp"
	//#include "programs/tetrex/tetrex.hpp"

int main (int argc, char** argv) {
	int exitcode = EXIT_SUCCESS;
	log("Program started.");

	// Clean up SDL when program quits:
		atexit(SDL_Quit);   // Free resources

	// CREATE SELECTED PROGRAM:
	// TODO: Automatize according to selected program target:
		Program *program = new Program();
		//Program *program = new SFEdemo();
		//Program *program = new Cavebombers();
		//Program *program = new Pinball();
		//Program *program = new PubLiippari();
		//Program *program = new Rocketz();
		//Program *program = new Tetrex();

	// INITIALIZATIONS
		if (!program->init()) {
			log("Error in program init.");
			exit (EXIT_FAILURE);
		}

	if (!program->mainloop()) {
		log("Error in program mainloop.");
		exit (EXIT_FAILURE);
	}

	// EXIT PROGRAM:
		// FREE RESOURCES:
		printf("Run time: %i ms, Frames drawn: %i, Overall fps: %f, Desired fps: %i\n",
			program->display->get_runtime(),
			program->display->get_framecount(),
			program->display->get_totalfps(),
			program->display->get_desiredfps());
		delete program;

	log("Program finished.");
	return exitcode;
	//exit (EXIT_SUCCESS);
}
