/*
	SF-Engine

	This file has routines for networking / sockets.
*/

#ifndef NETWORK_HPP
	#define NETWORK_HPP

	#include <string>

	class Link {
		// null-modem cable / serial port link
		bool send();
	};

	class Server {
		//socket
		unsigned short port;
		bool disconnect();
	};

	class Client {
		std::string remote_host;
		//socket
		unsigned short port;
		bool connect();
		bool disconnect();
	};

#endif // NETWORK_HPP
