/*
TODO:
- One vector for all goods for sale
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
			std::vector<Vehicle*> vehicles;
			std::vector<Weapon*> weapons;
			std::vector<Shield*> shields;
			std::vector<Gadget*> gadgets;
			std::vector<Item*> items;
			void randomize();
			void list_vehicles();
			void list_wapons();
			void list_shields();
			void list_gadgets();
			void list_items();
			void buy();
			void sell();
			bool execute();
	};

#endif // SHOP_HPP
