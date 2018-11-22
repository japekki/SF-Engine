#ifndef PROGRAM_CAVEBOMBERS_HPP
	#define PROGRAM_CAVEBOMBERS_HPP

	#include "program.hpp"

	// FILE NAMES:
		#define DATAPATH "../data/"

	class Cavebombers : public Program {
		public:
			Cavebombers();
			~Cavebombers();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_CAVEBOMBERS_HPP
