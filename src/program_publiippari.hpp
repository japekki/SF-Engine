#ifndef PROGRAM_PUBLIIPPARI_HPP
	#define PROGRAM_PUBLIIPPARI_HPP

	#include "program.hpp"

	// FILE NAMES:
		#define DATAPATH ""
		#define FILENAME_LOGO DATAPATH "logo.png"
		//#define FILENAME_KANNIKALA1 DATAPATH "kannikala1.png"
		//#define FILENAME_KANNIKALA2 DATAPATH "kannikala2.png"

	class PubLiippari : public Program {
		public:
			PubLiippari();
			~PubLiippari();
			bool init() override;
			bool mainloop() override;
	};

#endif // PROGRAM_PUBLIIPPARI_HPP
