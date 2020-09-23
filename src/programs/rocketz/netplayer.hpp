#ifndef NETPLAYER_HPP
	#define NETPLAYER_HPP

	#include "network.hpp"
	#include "player.hpp"

	// Forward declarations:
		// class Server;

	class Player_actions {
	};

	class ClientPlayer : public Player {
		public:
			ClientPlayer(Gameplay* gameplay);
			~ClientPlayer();
			Player_actions actions;
			bool send_actions();
	};

	class ServerPlayer : public Player {
		//private:
		public:
			ServerPlayer(Gameplay* gameplay);
			~ServerPlayer();
			Player_actions actions;
			bool receive_actions();
			void execute() override;
	};

#endif // NETPLAYER_HPP
