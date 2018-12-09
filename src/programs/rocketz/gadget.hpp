#ifndef GADGET_HPP
	#define GADGET_HPP

	#include "projectile.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_BOULDER DATAPATH "boulder.wav"
			#define FILENAME_SOUND_LADDERS DATAPATH "ladders.wav"

	class Gadget : public Polygon2D, public Projectile2D {
		// To be planted, not collectible, can be moved with tractor beam etc.
		// TODO: think this over
		bool can_float;
		bool works_under_water;
		bool sabotable;
		bool sabotaged;
		//unsigned short buy_price;
		//unsigned short sell_price;
	};

	class Gadget_anchor : public Gadget {
		// Attaches to vehicle, sticks to ground
	};

	class Gadget_boulder : public Gadget {
		// Stones rolling down a hill, crushing stuff
	};

	class Gadget_hose : public Gadget {
		// Water goes trough this, connects to pump
	};

	class Gadget_ladders : public Gadget {
		// For humans to climb up and down
		// Can go vertically, horizontally (bridge) or diagonally
		Coordinate2D starting_point;
		Coordinate2D ending_point;
		// TODO: what happens when hit in the middle
	};

	class Gadget_pump : public Gadget {
		// Pumps water, connects to hose
		void pump();
	};

	class Gadget_torch : public Gadget {
		// Creates light, like a torch or candle
	};

	class Gadget_tunnel : public Gadget {
		// Pipe or tunnel, humans and vehicles can go trough this, water can flow trough this
	};

#endif // GADGET_HPP
