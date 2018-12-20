#ifndef RAIN_HPP
	#define RAIN_HPP

	#define RAIN_NONE 0
	#define RAIN_WATER 1
	#define RAIN_SNOW 2
	#define RAIN_LAND 3
	#define RAIN_LAVA 4
	#define RAIN_BOMB 5
	#define RAIN_ITEM 6

	class Rain {
		unsigned char type = RAIN_WATER;
		unsigned int intensity;
		void makerain();
		virtual void execute();
	};

#endif // RAIN_HPP
