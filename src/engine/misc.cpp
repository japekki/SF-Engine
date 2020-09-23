#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
#include <filesystem>
#include "options.hpp"
#include "misc.hpp"

std::string add_leading_zeros(int number, unsigned char total_digits) {
	// FIXME: Doesn't work with negative numbers
	// TODO: Use std::setw and std::setfill
	std::string result = std::to_string(number);
	char count = total_digits - result.length();
	if (count > 0)
		for (unsigned char i=0; i<count; i++)
			result = "0" + result;
	return result;
}

//std::string add_trailing_zeros(uint32_t number, unsigned char count) {
//}

std::string get_current_timestamp() {
	// Make timestamp string
		time_t now = time(0);
		tm *ltm = localtime(&now);

		std::string timestamp;
		timestamp =
			std::to_string(1900 + ltm->tm_year) +
			add_leading_zeros(1 + ltm->tm_mon, 2) +
			add_leading_zeros(ltm->tm_mday, 2) + "-" +
			add_leading_zeros(ltm->tm_hour, 2) +
			add_leading_zeros(ltm->tm_min, 2) +
			add_leading_zeros(ltm->tm_sec, 2);
		return timestamp;
}

/*
https://thispointer.com/c-get-the-list-of-all-files-in-a-given-directory-and-its-sub-directories-using-boost-c17/

Get the list of all files in given directory and its sub directories.

Arguments:
	dirPath = Path of directory to be traversed
	dirSkipList = List of folder names to be skipped

Returns:
	vector containing paths of all the files in given directory and its sub directories
*/

//std::vector<std::string> getAllFilesInDir(const std::string &dirPath, const std::vector<std::string> dirSkipList = { }) {
std::vector<std::string> getAllFilesInDir(const std::string &dirPath) {
	// Create a vector of string
	std::vector<std::string> listOfFiles;
	try {
		// Check if given path exists and points to a directory
		if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath)) {
			// Create a Recursive Directory Iterator object and points to the starting of directory
			std::filesystem::recursive_directory_iterator iter(dirPath);
			// Create a Recursive Directory Iterator object pointing to end.
			std::filesystem::recursive_directory_iterator end;
			// Iterate till end
			while (iter != end) {
				// Check if current entry is a directory and if exists in skip list
				if (std::filesystem::is_directory(iter->path())
				//&& (std::find(
				//	dirSkipList.begin(),
				//	dirSkipList.end(),
				//	iter->path().filename())
				// != dirSkipList.end())
				) {
					// Skip the iteration of current directory pointed by iterator
					#ifdef USING_BOOST
						// Boost Fileystsem  API to skip current directory iteration
						iter.no_push();
					#else
						// c++17 Filesystem API to skip current directory iteration
						iter.disable_recursion_pending();
					#endif
				} else {
					// Add the name in vector
					listOfFiles.push_back(iter->path().string());
				}
				std::error_code ec;
				// Increment the iterator to point to next entry in recursive iteration
				iter.increment(ec);
				if (ec)
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
			}
		}
	}
	catch (std::system_error & e) {
		std::cerr << "Exception :: " << e.what();
		//log("Exception :: " << e.what());
	}
	return listOfFiles;
}

std::string lowercase(std::string text) {
	for (uint32_t x=0; x<text.length(); x++)
		if (text[x] >= 'A' && text[x] <= 'Z') text[x]-= ('A'-'a');
	return text;
}

std::string uppercase(std::string text) {
	for (uint32_t x=0; x<text.length(); x++)
		if (text[x] >= 'a' && text[x] <= 'z') text[x]+= ('A'-'a');
	return text;
}

std::string togglecase(std::string text) {
	for (uint32_t x=0; x<text.length(); x++) {
		if (text[x] >= 'A' && text[x] <= 'Z') text[x]-= ('A'-'a');
		else if (text[x] >= 'a' && text[x] <= 'z') text[x]+= ('A'-'a');
	}
	return text;
}

std::string reverse(std::string text) {
	std::string copy = text;
	for (uint32_t index=0; index<text.length(); index++)
		copy[index]=text[text.length()-index-1];
	return copy;
}

std::vector<std::string> split(std::string text, std::string delimiter) {
	std::vector<std::string> result;
	while(text.size()) {
		int index = text.find(delimiter);	// NOTE: text.find() can return -1 for index, so index has to be signed
		if(index != std::string::npos) {	// FIXME: Gives a warning because index is signed
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

void log(const std::string &msg) {
	std::cout << "[" << get_current_timestamp() << "] "<< msg << std::endl;
}

std::string get_cmdline_parameter_value(int argc, char** argv, std::string parameter_name) {
	std::string value;
	if (argc >= 3) {
		for(int i=0; i<argc; i++) {
			if ((argv[i] == "/" + parameter_name)
			or (argv[i] == "-" + parameter_name))
				value = argv[i+1];
		}
	}
	return value;
}
