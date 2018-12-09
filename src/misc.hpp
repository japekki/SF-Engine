/*
	SF-Engine

	This file has miscellaneous routines.
*/

// TODO: Check what is already done in standard library

#ifndef MISC_HPP
	#define MISC_HPP

	#include <iostream>
	#include "options.hpp"

	#include <string>
	#include <vector>

	void log(const std::string &msg);

	#ifdef WITH_DEBUGMSG
		void debugmsg(const std::string &msg);
	#endif // WITH_DEBUGMSG

	std::string lowercase(std::string text);
	std::string uppercase(std::string text);
	std::string togglecase(std::string text);
	std::string reverse(std::string text);
	std::vector<std::string> split(std::string text, std::string delimiter);

#endif // MISC_HPP
