#ifndef PLAYER_HPP
	#define PLAYER_HPP

	#define PLAYER_TYPE_CPU 0
	#define PLAYER_TYPE_HUMAN 1
	#define PLAYER_TYPE_REMOTE 2

	#include <string>

	class Player {
		std::string name;
		unsigned char lives = 3;	// Re-spawn at base if lives left
		unsigned char type = 0;		// computer or human
		bool remote;				// remote if controlled over network
		unsigned int money = 0;
		//Client client;	// for network game
		void surrender();
	};

#endif // PLAYER_HPP
