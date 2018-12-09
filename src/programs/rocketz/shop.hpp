/*
TODO:
- Should a Shop also be a Building?
*/

#ifndef SHOP_HPP
	#define SHOP_HPP

	#include <vector>
	#include "gadget.hpp"
	#include "item.hpp"
	#include "shield.hpp"
	#include "vehicle.hpp"
	#include "weapon.hpp"
	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_BUY DATAPATH "buy.wav"
			#define FILENAME_SOUND_NOTENOUGHMONEY DATAPATH "notenoughmoney.wav"
			#define FILENAME_SOUND_SELL DATAPATH "sell.wav"

	class Shop {
		public:
			std::vector<Vehicle*> vehicles_available;
			std::vector<Weapon*> weapons_available;
			std::vector<Shield*> shields_available;
			std::vector<Gadget*> gadgets_available;
			std::vector<Item*> items_available;
			void list_vehicles();
			void list_wapons();
			void list_shields();
			void list_gadgets();
			void list_items();
	};

#endif // SHOP_HPP
