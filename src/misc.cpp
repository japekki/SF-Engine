//#include "misc.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> split(string string_, char delimiter)    // TODO: Ei toimi
{
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
	   for (int x=0; x<arg.length(); x++)
	   {
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
	string copy=fullname;
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

/*
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
