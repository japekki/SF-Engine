/*
	SF-Engine

	This file has routines for networking / sockets and serial cable link.
*/

#ifndef NETWORK_HPP
	#define NETWORK_HPP

	#include <string>
	#include <SDL_net.h>

	class Link {
		// null-modem cable / serial port link
		bool works;	// Change to false if something goes wrong
		bool send();
	};

	class Server {
		bool works;	// Change to false if something goes wrong
		//socket
		uint16_t port;
		bool disconnect();
	};

	class Client {
		bool works;	// Change to false if something goes wrong
		std::string remote_host;
		//socket
		uint16_t port;
		bool connect();
		bool disconnect();
		bool send();
	};

#endif // NETWORK_HPP
