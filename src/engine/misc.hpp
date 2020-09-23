/*
	SF-Engine

	This file has miscellaneous routines.
*/

#ifndef MISC_HPP
	#define MISC_HPP

	#include "options.hpp"
	#include <iostream>
	#include <string>
	#include <vector>

	void log(const std::string &msg);
	std::string get_cmdline_parameter_value(int argc, char** argv, std::string parameter_name);
	std::string add_leading_zeros(int number, unsigned char total_digits);
	std::string get_current_timestamp();
	std::vector<std::string> getAllFilesInDir(const std::string &dirPath);
	std::string lowercase(std::string text);
	std::string uppercase(std::string text);
	std::string togglecase(std::string text);
	std::string reverse(std::string text);
	std::vector<std::string> split(std::string text, std::string delimiter);

	// TODO:
		//std::string add_trailing_zeros(uint32_t number, unsigned char total_digits);
		//std::string add_leading_zeros(int number, unsigned char count);
		//std::string add_trailing_zeros(int number, unsigned char count);
		//std::string crop_leading_zeros(std::string text);
		//std::string crop_trailing_zeros(std::string text);
		//void list_directories(std::string path);

#endif // MISC_HPP
