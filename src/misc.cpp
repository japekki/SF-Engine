/*
	SF-Engine

	This file has miscellaneous routines.
*/

#include <iostream>
//#include <sstream>
//#include <ctime>
#include "options.hpp"
//#include "misc.hpp"

void log(const std::string &msg) {
	// Print timestamp
	// FIXME
		//time_t now = time(0);
		//tm *ltm = localtime(&now);
		//std::cout << "[" << 1900 + ltm->tm_year;
		//std::cout << "-" << 1 + ltm->tm_mon;
		//std::cout << "-" << ltm->tm_mday;
		//std::cout << " " << 1 + ltm->tm_hour;
		//std::cout << ":" << 1 + ltm->tm_min;
		//std::cout << ":" << 1 + ltm->tm_sec << "] ";
		// TODO: Format all values to 2 digits ("2" -> "02")
	// Print message:
		std::cout << msg << std::endl;
}

#ifdef WITH_DEBUGMSG
void debugmsg(const std::string &msg) {
	std::cout << "DEBUG: " << msg << std::endl;
}
#endif // WITH_DEBUGMSG

/*
#include <string>
#include <vector>

vector<string> split(string string_, char delimiter) {	// FIXME
	vector<string> results;
	int wordcount = 0;
	for (int i=0; i<string_.length(); i++) {
		if (string_.at(i) == delimiter) {
			wordcount++;
		}
		else {
			//results.at(wordcount).append(string_.at(i)) );
		}
	}
	return results;
}

string lowercase(string arg) {
	for (int x=0; x<arg.length(); x++) {
		if (arg[x] >= 'A' && arg[x] <= 'Z') arg[x]-= ('A'-'a');
	}
	return arg;
}

string uppercase(string arg) {
	for (int x=0; x<arg.length(); x++) {
		if (arg[x] >= 'a' && arg[x] <= 'z') arg[x]+= ('A'-'a');
	}
	return arg;
}

string reverse(string fullname) {
	string copy = fullname;
	for (int indx=0; indx<fullname.length(); indx++) {
		copy[indx]=fullname[fullname.length()-indx-1];
	}
	return copy;
}

string togglecase(string arg) {
	for (int x=0; x<arg.length(); x++) {
		if (arg[x] >= 'A' && arg[x] <= 'Z') arg[x]-= ('A'-'a');
		else if (arg[x] >= 'a' && arg[x] <= 'z') arg[x]+= ('A'-'a');
	}
	return arg;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	return split(s, delim, elems);
}

*/
