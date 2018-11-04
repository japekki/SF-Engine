#ifndef EFFUX_ARCHIVE_HPP
	#define EFFUX_ARCHIVE_HPP

	#include <SDL/SDL.h>

	#include "entity.hpp"

	//    void effux_hattu(Uint32 time);
	//    void effux_entity(Uint32 time, Entity Entiteetti);

		void effux_entity(Uint32 time, Entity Entiteetti, SDL_Surface *sdlsurface);
		void effux1(Uint32 time, SDL_Surface *sdlsurface);
		void effux2(Uint32 time, SDL_Surface *sdlsurface);
		void effux3(Uint32 time, SDL_Surface *sdlsurface);
		void effux_geomelem(Uint32 time, SDL_Surface *sdlsurface);
		void effux_chessplane(Uint32 time, SDL_Surface *sdlsurface);
		void effux_rainbow(Uint32 time, SDL_Surface *sdlsurface);
		//void effux_rotozoomer(Uint32 time, SDL_Surface *image, SDL_Surface *sdlsurface);
		//void effux_bitmapweaver(Uint32 time, SDL_Surface *bitmap, SDL_Surface *sdlsurface);
		void effux_luukku(Uint32 time, SDL_Surface *sdlsurface);
		void effux_blur(SDL_Surface *sdlsurface);
		void effux_juna(Uint8 index, SDL_Surface *sdlsurface);
		void effux_viivat(Uint8 index, SDL_Surface *sdlsurface);

		extern Uint32 colorRed;
		extern Uint32 colorGreen;
		extern Uint32 colorBlue;
		extern Uint32 colorWhite;
		extern Uint32 colorBlack;
		extern Uint32 colorYellow;
		extern Uint32 colorCyan;
		extern Uint32 colorOrange;
		extern Uint32 colorViolet;
		extern Uint32 colorBrown;
		extern Uint32 colorGrey;

		class EffuxRinkula {
			public:
				Uint16 width;
				Uint16 height;
				std::vector<bool> circles;
				EffuxRinkula();
				void init(Uint16 width_, Uint16 height_);
				void draw(Uint32 time, bool both, SDL_Surface *sdlsurface);
		};

#endif // EFFUX_ARCHIVE_HPP
