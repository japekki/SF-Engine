#ifndef ZBUF_HPP
	#define ZBUF_HPP

	#include <vector>

	class Zbuf {
		private:
			unsigned short width = 0;
			unsigned short height = 0;
		public:
			std::vector<float> z;
			Zbuf();
			Zbuf(unsigned short width, unsigned short height);
			~Zbuf();
			void resize(unsigned short width, unsigned short height);
			void reset();
	};

#endif // ZBUF_HPP
