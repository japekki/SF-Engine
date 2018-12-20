#ifndef ITEM_HPP
	#define ITEM_HPP

	#include "gameobject.hpp"

	// Forward declarations:
		class Human;

	class Item : public Gameobject {
		// Collectible items by humans, not by vehicles.
		// Items are used immediately when touched by human, or collected to base when carried by hoarders.
		// Usually some sort of power-ups.
		// Can be transported with tractor beam, or crushed by tank or blasted by weapon.
		unsigned short buy_price;
		unsigned short sell_price;
	};

	class Item_extralife : public Item {
	};

	class Item_medkit : public Item {
		// Heals a human
		unsigned short health;
		void heal(Human *human);
	};

	class Item_money : public Item {
		unsigned short amount;
	};

#endif // ITEM_HPP
