#ifndef GADGET_HPP
	#define GADGET_HPP

	#include "gamespace.hpp"

	// Forward declarations:
		//

	class Radar {
		// Radar / Sonar, like a mini-map
		unsigned char angle;
		unsigned char rotation_speed;
		uint32_t range;
	};

	class Gadget : public Gameblob {
		// To be planted, not collectible, can be moved with tractor beam etc.
		bool can_float;
		bool works_under_water;
		bool sabotable;
		bool sabotaged;
		//uint16_t buy_price;
		//uint16_t sell_price;
	};

	class Gadget_anchor : public Gadget {
		// Attaches to vehicle, sticks to ground
		void execute();
	};

	class Gadget_boulder : public Gadget {
		// Stones rolling down a hill, crushing stuff
		//void execute();
	};

	class Gadget_hose : public Gadget {
		// Water goes trough this, connects to pump
		//void execute();
	};

	class Gadget_ladders : public Gadget {
		// For humans to climb up and down
		// Can go vertically, horizontally (bridge) or diagonally
		Point* starting_point;
		Point* ending_point;
		// TODO: what happens when hit in the middle
		void execute();
	};

	class Gadget_pump : public Gadget {
		// Pumps water, connects to hose
		void execute();
	};

	class Gadget_torch : public Gadget {
		// Creates light, like a torch or candle
		void execute();
	};

	class Gadget_tunnel : public Gadget {
		// Pipe or tunnel, humans and vehicles can go trough this, water can flow trough this
		void execute();
	};

#endif // GADGET_HPP
