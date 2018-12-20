#include <iostream>
#include <sstream>
//#include <ctime>
#include <string>
#include <vector>
#include "options.hpp"
#include "misc.hpp"

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

std::string lowercase(std::string text) {
	for (unsigned int x=0; x<text.length(); x++)
		if (text[x] >= 'A' && text[x] <= 'Z') text[x]-= ('A'-'a');
	return text;
}

std::string uppercase(std::string text) {
	for (unsigned int x=0; x<text.length(); x++)
		if (text[x] >= 'a' && text[x] <= 'z') text[x]+= ('A'-'a');
	return text;
}

std::string togglecase(std::string text) {
	for (unsigned int x=0; x<text.length(); x++) {
		if (text[x] >= 'A' && text[x] <= 'Z') text[x]-= ('A'-'a');
		else if (text[x] >= 'a' && text[x] <= 'z') text[x]+= ('A'-'a');
	}
	return text;
}

std::string reverse(std::string text) {
	std::string copy = text;
	for (unsigned int index=0; index<text.length(); index++)
		copy[index]=text[text.length()-index-1];
	return copy;
}

std::vector<std::string> split(std::string text, std::string delimiter) {
	std::vector<std::string> result;
	while(text.size()) {
		int index = text.find(delimiter);
		if(index != std::string::npos) {
			result.push_back(text.substr(0,index));
			text = text.substr(index + delimiter.size());
			if(text.size() == 0)result.push_back(text);
		} else {
			result.push_back(text);
			text = "";
		}
	}
	return result;
}
