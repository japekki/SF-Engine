#ifndef ZBUF_HPP
	#define ZBUF_HPP

	#include <stdint.h>
	#include <vector>

	class Zbuf {
		private:
			uint16_t width = 0;
			uint16_t height = 0;
		public:
			std::vector<float> z;
			Zbuf();
			Zbuf(uint16_t width, uint16_t height);
			~Zbuf();
			void resize(uint16_t width, uint16_t height);
			void reset();
	};

#endif // ZBUF_HPP
