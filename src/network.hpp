/*
	SF-Engine

	This file has routines for networking / sockets and serial cable link.
*/

#ifndef NETWORK_HPP
	#define NETWORK_HPP

	#include <string>

	class Link {
		bool works;	// Change to false if something goes wrong
		// null-modem cable / serial port link
		bool send();
	};

	class Server {
		bool works;	// Change to false if something goes wrong
		//socket
		unsigned short port;
		bool disconnect();
	};

	class Client {
		bool works;	// Change to false if something goes wrong
		std::string remote_host;
		//socket
		unsigned short port;
		bool connect();
		bool disconnect();
		bool send();
	};

#endif // NETWORK_HPP
