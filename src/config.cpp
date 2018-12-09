#include "config.hpp"

Config::Config(std::string filename) {
	this->filename = filename;
}

/*
bool read_file () {
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
		this->works = works and conf_file.is_open();	// Preserver previous false
		conf_file.close();
	} else {
		log("ERROR reading config file " << filename);
		this->works = false;
	}

	return this->works;
}
*/
