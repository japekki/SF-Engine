#include <SDL.h>
#include "misc.hpp"

#include "pinball.hpp"	// Program to execute

int main (int argc, char** argv) {
	int exitcode = EXIT_SUCCESS;

	// CREATE PROGRAM:
		Program *program = new Pinball(argc, argv);

	// INITIALIZATIONS
		if (!program->init()) {
			log("Error in program init.");
			exit (EXIT_FAILURE);
		}

	// START MAIN LOOP:
		if (!program->mainloop()) {
			log("Error in program mainloop.");
			exit (EXIT_FAILURE);
		}

	// EXIT PROGRAM:
		delete program;

	return exitcode;
	//exit (EXIT_SUCCESS);
}
