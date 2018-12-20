/*
TODO:
- Should a Shop also be a Building?
*/

#ifndef SHOP_HPP
	#define SHOP_HPP

	#include <vector>

	// Forward declarations:
		class Vehicle;
		class Weapon;
		class Shield;
		class Gadget;
		class Item;

	class Shop {
		public:
			std::vector<Vehicle> vehicles_available;
			std::vector<Weapon> weapons_available;
			std::vector<Shield> shields_available;
			std::vector<Gadget> gadgets_available;
			std::vector<Item> items_available;
			void list_vehicles();
			void list_wapons();
			void list_shields();
			void list_gadgets();
			void list_items();
			void buy();
			void sell();
	};

#endif // SHOP_HPP
