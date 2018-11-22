#ifndef PROGRAM_FOOBAR_HPP
	#define PROGRAM_FOOBAR_HPP

	#include "program.hpp"

	class Foobardemo : public Program {
		public:
			Foobardemo();
			~Foobardemo();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_FOOBAR_HPP
