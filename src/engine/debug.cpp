#include "debug.hpp"

#ifdef WITH_DEBUGMSG
	void debugmsg(const std::string &msg) {
		std::cout << "DEBUG: " << msg << std::endl;
	}
#endif // WITH_DEBUGMSG
