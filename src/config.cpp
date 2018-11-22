/*
bool read_configfile () {
	bool works = true; // Change to false if something goes wrong
	std::string filename = "demo.cfg";
	std::string parameter, value;

	std::cout << "Loading parameters from file " << filename << ": ";

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
		std::cerr << "ERROR reading config file " << filename << std::endl;
		works = false;
	}

	//vector<string> testi;
	//string testi2;
	//testi = split("hey hey yo yo", ' ');
	//cout << testi[1] << endl;

	return works;
}
*/
