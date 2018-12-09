/*
	SF-Engine

	This file has basic routines for drawing graphics.
*/

/*
TODO:
- Scroller for textures, single and parallax
- Render to specific target texture.
- Optional feature: recalculate/resize stuff when desktop fullscreen toggles, resolution changes, window resizes or target texture resizes
- Don't try to recreate/wrap too much stuff, rely more on direct SDL API calls throughout all code instead
- Take some routines out from Grapher class and separate into modular effux files
- Optimize:
	- Static and streaming textures, texture (un)locking, SDL_RENDERER_ACCELERATED
	- Different pixel formats
*/

#ifndef GRAPHER_HPP
	#define GRAPHER_HPP

	#include <string>
	#include <SDL.h>
	#include <SDL_ttf.h>
	#include "geom.hpp"
	#include "zbuf.hpp"

	struct simplesprite {
		SDL_Texture *sdltexture = nullptr;
		SDL_Rect rect;
	};

	class Grapher {
		public:
			bool works = true;	// Change to false if something goes wrong
			//unsigned int pixelformat;	// TODO
			int width;
			int height;
			Zbuf *zbuf;
			SDL_Texture* load_imagefile(const char* filename);
			TTF_Font* load_font(const char* filename, int size);	// returns NULL if not successful
			SDL_Texture* create_textmultiline_texture(std::string textline, TTF_Font *font, SDL_Color color);
			SDL_Texture* create_textline_texture(std::string text, TTF_Font *font, SDL_Color color);
			bool draw_text(std::string text, TTF_Font *font, SDL_Color color, int x, int y);
			bool draw_texture(SDL_Texture* texture, SDL_Rect rect);
			// TODO:
				//bool draw_texture(SDL_Texture* texture, SDL_Rect rect, Uint8 opacity);
				//bool draw_texture(SDL_Texture* texture, SDL_Rect rect, int width, int height);
				//bool draw_texture(SDL_Texture* texture, SDL_Rect rect,int width, int height, Uint8 opacity);
			bool draw_texture(SDL_Texture* texture, int x, int y);
			// TODO:
				//bool draw_texture(SDL_Texture* texture, int x, int y, Uint8 opacity);
				//bool draw_texture(SDL_Texture* texture, int x, int y, int width, int height);
				//bool draw_texture(SDL_Texture* texture, int x, int y, int width, int height, Uint8 opacity);
			//bool draw_texture(SDL_Texture* texture, int x, int y, Uint8 opacity);
			bool draw_texture(simplesprite &sprite);
			//void draw_hline(int x1, int x2, int y, unsigned int color);
			void draw_triangle(Triangle2D *triangle);
			void draw_triangle(Triangle3D *triangle);
			void draw_polygon(Polygon2D *polygon);
			void draw_polygon(Polygon3D *polygon);
			SDL_Renderer *sdlrenderer;
			bool with_coordinategrid = false;
			Coordinategrid *coordinategrid;
	};

	SDL_Texture* create_alphacircle(Grapher *grapher, Uint32 color);

#endif // GRAPHER_HPP
