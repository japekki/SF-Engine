#include <SDL.h>
#include "misc.hpp"

#include "sfe_benchmark.hpp"	// Program to execute

int main (int argc, char** argv) {
	int exitcode = EXIT_SUCCESS;

	// CREATE PROGRAM:
		Program *program = new SFE_Benchmark(argc, argv);

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
