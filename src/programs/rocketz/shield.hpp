/*
TODO:
- Human shields
*/

#ifndef SHIELD_HPP
	#define SHIELD_HPP

	#include <string>

	class Shield {
		public:
			// Always on, unlike Weapon
			std::string name;
			std::string description;
			bool gets_damage;
			unsigned int condition;	// 0 if worn out
			bool works_under_water;
			unsigned char level;	// How powerful the shield is
			unsigned short buy_price;
			unsigned short sell_price;
			//Polygon2D picture;	// Or Sprite - shows up in shop and menus
			// sound when used
	};

	class Shield_bounce : public Shield {
		Shield_bounce();
	};

	class Shield_cold : public Shield {
		Shield_cold();
	};

	class Shield_electro : public Shield {
		Shield_electro();
	};

	class Shield_hot : public Shield {
		Shield_hot();
	};

	class Shield_inertialdamper : public Shield {
		Shield_inertialdamper();
	};

	class Shield_lifesteal : public Shield {
		Shield_lifesteal();
	};

	class Shield_lightscreen : public Shield {
		Shield_lightscreen();
	};

	class Shield_mirror : public Shield {
		Shield_mirror();
	};

	class Shield_repel : public Shield {
		Shield_repel();
	};

#endif // SHIELD_HPP
