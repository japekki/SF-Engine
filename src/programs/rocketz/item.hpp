// Collectible items by humans, not by vehicles (?)
// Items are used immediately when touched by human, or collected to base when carried by hoarders.
// Usually some sort of power-ups.
// Can be transported with tractor beam, or crushed by tank or blasted by weapon.

// TODO:
// - Do not collide items and their collectors (Human, Vehicle)
// - No item gravity until first collision (or something)
// - Share same texture among items of same type

#ifndef ITEM_HPP
	#define ITEM_HPP

	#include "gamespace.hpp"

	// Forward declarations:
		class Human;

	class Item : public Gameblob {
		public:
			uint16_t buy_price = 0;
			uint16_t sell_price = 0;
			Item(Gameplay* gameplay);
			virtual ~Item();
			void draw();
			//virtual void execute(Gameblob* collector) = 0;
			//void explode();
	};

	class ItemText : public Item {
		// Items that are drawn as text
		public:
			SDL_Texture* texture;
			ItemText(Gameplay* gameplay);
			virtual void draw();
	};

	class Item_extralife : public ItemText {
		public:
			uint16_t amount = 1;
			Item_extralife(Gameplay* gameplay);
			~Item_extralife();
			void execute(Gameblob* collector);
	};

	class Item_medkit : public ItemText {
		// Heals a human
		public:
			uint16_t amount = 50;
			Item_medkit(Gameplay* gameplay);
			~Item_medkit();
			void execute(Gameblob* collector);
	};

	class Item_money : public ItemText {
		public:
			uint16_t amount = 1000;
			Item_money(Gameplay* gameplay);
			~Item_money();
			void execute(Gameblob* collector);
	};

	class Item_fuel : public ItemText {
		public:
			uint16_t amount = 1000;
			Item_fuel(Gameplay* gameplay);
			~Item_fuel();
			void execute(Gameblob* collector);
	};

#endif // ITEM_HPP
