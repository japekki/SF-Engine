#ifndef MISC_HPP
	#define MISC_HPP

	#include <iostream>
	#include "options.hpp"

/*
	#include <string>

	// TODO: Check what is already done in standard library

	vector<string> split(string string_, char delimiter);
	string lowercase(string arg);
	string uppercase(string arg);
	string reverse(string fullname);
	string togglecase(string arg);
*/

	void log(const std::string &msg);
	#ifdef WITH_DEBUGMSG
		void debugmsg(const std::string &msg);
	#endif // WITH_DEBUGMSG

#endif // MISC_HPP
