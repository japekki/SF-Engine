/*
	SF-Engine

	This file has routines for configuration (file) handling.
*/

// TODO:
// - Config format doc
// - array for parameters

#ifndef CONFIG_HPP
	#define CONFIG_HPP

	#include <string>

	class Config {
		std::string filename;
		Config(std::string filename);
		bool read();
		bool save();
	};

#endif // CONFIG_HPP
