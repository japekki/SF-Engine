/*
	SF-Engine

	This file has basic routines for drawing graphics.
*/

/*
TODO:
- Text shadow with alpha
- Outline
- Color shade/fade
- Scroller for textures, single and parallax
- Don't try to recreate/wrap too much stuff, rely more on direct SDL API calls
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

	// LAYER TYPES:
		#define LAYER_NONE 0
		#define LAYER_COLOR 1
		#define LAYER_BITMAP 2
		#define LAYER_EFFUX 3

	class Layer {
		public:
			Layer();
			~Layer();
			unsigned char type = LAYER_NONE;
			SDL_Texture *sdltexture;
			// Effux* effux;
	};

	class Simplesprite {
		public:
			SDL_Texture *sdltexture = nullptr;
			SDL_Rect rect;
	};

	class Grapher {
		public:
			bool works = true;	// Change to false if something goes wrong
			//unsigned int pixelformat;	// TODO
			int width;
			int height;
			//Zbuf *zbuf;
			SDL_Surface* load_surface(const char* filename);
			SDL_Texture* load_texture(const char* filename);
			bool init_fontsystem();
			void deinit_fontsystem();
			TTF_Font* load_font(const char* filename, int size);	// returns NULL if not successful
			SDL_Texture* create_textmultiline_texture(std::string textline, TTF_Font *font, SDL_Color color);
			SDL_Texture* create_textline_texture(std::string text, TTF_Font *font, SDL_Color color);
			bool colorfade(SDL_Texture* &texture, Uint32 color);
			Grapher();
			bool draw_text(std::string text, TTF_Font *font, SDL_Color color, int x, int y);
			bool draw_texture(SDL_Texture* texture, SDL_Rect rect);
			bool draw_texture(Simplesprite* texture);
			//bool draw_texture(SDL_Texture* texture, SDL_Rect rect, int width, int height);
			bool draw_texture(SDL_Texture* texture, int x, int y);
			//bool draw_texture(SDL_Texture* texture, int x, int y, int width, int height);
			bool draw_texture(Simplesprite &sprite);
			//void draw_hline(int x1, int x2, int y, unsigned int color);
			void draw_triangle(Triangle* triangle);
			void draw_polygon(Polygon *polygon);
			SDL_Renderer *sdlrenderer;
			Coordinategrid grid;
			bool with_grid = false;
			bool use_grid;
			void set_grid(float x_min, float y_min, float x_max, float y_max);
			Point* apply_grid(Point* coordinate);
	};

	SDL_Texture* create_alphacircle(Grapher *grapher, Uint32 color);

#endif // GRAPHER_HPP
