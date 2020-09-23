/*
TODO:
- Shields for other blobs (Human, Building)
*/

#ifndef SHIELD_HPP
	#define SHIELD_HPP

	#include <string>

	class Shield {
		public:
			// Always on, unlike Weapon
			std::string name;
			std::string description;
			bool activated = false;
			bool always_on = false;
			bool gets_damage = true;		// is the shield weakening from hits?
			uint32_t condition = 0;			// 0 if worn out
			bool works_under_water = true;
			unsigned char level = 1;		// How powerful the shield is
			void activate();
			void deactivate();
			uint16_t buy_price = 0;
			uint16_t sell_price = 0;
			// play sound when (de)activated or being in use
	};

	class Shield_bouncer : public Shield {
		Shield_bouncer();
	};

	class Shield_warmer : public Shield {
		Shield_warmer();
	};

	class Shield_knocker : public Shield {
		Shield_knocker();
	};

	class Shield_faraday : public Shield {
		Shield_faraday();
	};

	class Shield_cooler : public Shield {
		Shield_cooler();
	};

	class Shield_inertialdamper : public Shield {
		Shield_inertialdamper();
	};

	class Shield_unpenetrable : public Shield {
		Shield_unpenetrable();
	};

	class Shield_sunscreen : public Shield {
		Shield_sunscreen();
	};

	class Shield_mirror : public Shield {
		Shield_mirror();
	};

	class Shield_repeller : public Shield {
		Shield_repeller();
	};

#endif // SHIELD_HPP
