#ifndef RAIN_HPP
	#define RAIN_HPP

	class Rain {
		unsigned int intensity;
		void execute();
	};

	class Waterrain : public Rain {
	};

	class Snowrain : public Rain {
	};

	class Landrain : public Rain {
	};

	class Lavarain : public Rain {
	};

	class Bombrain : public Rain {
	};

	class Itemrain : public Rain {
	};

#endif // RAIN_HPP
