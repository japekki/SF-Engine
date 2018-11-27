/*
	SF-Engine

	This file has routines for configuration (file) handling.
*/

#include "config.hpp"

/*
bool read_configfile () {
	bool works = true; // Change to false if something goes wrong
	std::string filename = "program.cfg";
	std::string parameter, value;

	log("Loading parameters from file " << filename << ": ");

	std::string line;
	std::ifstream conf_file(filename.c_str(), std::ios::binary);   // Default?
	if (conf_file.is_open()) {
		while (!conf_file.eof()) {
			getline (conf_file, line);
			if (line.length() > 3) {
				// delete spaces and tabs
				// split string with '=' as delimiter

				//switch (parameter) {
				//	case "res_x":
				//		//monitor.set_width(value);
				//		break;
				//	case "res_y":
				//		//monitor.set_height(value);
				//		break;
				//	case "fps":
				//		//monitor.fps=value;
				//		break;
				//	case "fullscreen":
				//		//monitor.fullscreen=value;
				//		break;
				//	case "looping":
				//		//
				//		break;
				//	case "sound":
				//		//sound.with_sound=value;
				//		break;
				//	}

			}
		}
		works = conf_file.is_open();
		conf_file.close();
	} //if (conf_file.is_open())
	else {
		log("ERROR reading config file " << filename);
		works = false;
	}

	//vector<string> test;
	//string test2;
	//test = split("hey hey yo yo", ' ');
	//log(test[1]);

	return works;
}
*/
