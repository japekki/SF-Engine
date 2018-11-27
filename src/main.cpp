/*
	SF-Engine

	This is the main file where the program starts.
*/

#include <SDL.h>
#include "misc.hpp"
#include "display.hpp"

// Select program to build:
// TODO: Automatize according to selected program target:
	#include "program.hpp"		// Template program, included automatically by other program targets
	//#include "program_cavebombers.hpp"
	//#include "program_foobar.hpp"
	//#include "program_pinball.hpp"
	//#include "program_publiippari.hpp"
	//#include "program_rocketz.hpp"
	//#include "program_tetrex.hpp"

int main (int argc, char** argv) {
	int exitcode = EXIT_SUCCESS;
	log("Program started.");

	// Clean up SDL when program quits:
		atexit(SDL_Quit);   // Free resources

	// Create selected program:
	// TODO: Automatize according to selected program target:
		Program *program = new Program();
		//Program *program = new Cavebombers();
		//Program *program = new Foobardemo();
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
