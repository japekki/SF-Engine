#ifndef PROGRAM_TETREX_HPP
	#define PROGRAM_TETREX_HPP

	#include "program.hpp"

	// FILE NAMES:
		#define DATAPATH ""

	class Tetrex : public Program {
		public:
			Tetrex();
			~Tetrex();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_TETREX_HPP
