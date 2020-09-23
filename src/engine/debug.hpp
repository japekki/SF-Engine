/*
	SF-Engine

	This file has routines for debugging.
*/

#ifndef DEBUG_HPP
	#define DEBUG_HPP

	#ifdef WITH_DEBUGMSG
		/*
			Debugging messages:
				#define debug_errormsg_something "error"
				#define MSG_QUITERROR "Program aborted due to an error."
		*/
		void debugmsg(const std::string &msg);
	#endif // WITH_DEBUGMSG

#endif // DEBUG_HPP
