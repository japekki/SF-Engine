/*
	SF-Engine

	This file has basic routines for drawing graphics.
*/

/*
TODO:
- Viewports inside viewports with their own coordinate grids each
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
	#include "geometry.hpp"
	#include "effux.hpp"

	// LAYER TYPES:
		#define LAYER_NONE 0
		#define LAYER_COLOR 1
		#define LAYER_TEXTURE 2
		#define LAYER_EFFUX 3

	class Layer {
		public:
			Layer();
			~Layer();
			unsigned char type = LAYER_TEXTURE;
			SDL_Texture *texture;
	};

	class LayerEffux : public Effux, public Layer {
	};

	class Simplesprite {
		public:
			SDL_Texture *texture = nullptr;
			SDL_Rect rect;
			Simplesprite();
			Simplesprite(SDL_Texture* texture);
			~Simplesprite();
	};

	class Grapher {
		public:
			SDL_Renderer *renderer = nullptr;
			uint16_t width = 0;
			uint16_t height = 0;
			Coordinategrid grid;
			Grapher();
			virtual ~Grapher();
			//SDL_Texture* create_textmultiline_texture(std::string textline, TTF_Font *font, SDL_Color color);
			//SDL_Texture* create_textline_texture(std::string text, TTF_Font *font, SDL_Color color);
			bool draw_text(std::string text, TTF_Font *font, SDL_Color color, int x, int y);
			bool draw_text(std::string text, TTF_Font *font, uint32_t color, int x, int y);
			bool draw_texture(SDL_Texture* texture, SDL_Rect rect);
			bool draw_texture(Simplesprite* texture);
			//bool draw_texture(SDL_Texture* texture, SDL_Rect rect, int width, int height);
			bool draw_texture(SDL_Texture* texture);
			bool draw_texture(SDL_Texture* texture, int x, int y);
			bool draw_texture(SDL_Texture* texture, Point location);
			bool draw_texture(Simplesprite &sprite);
			//void draw_hline(int x1, int x2, int y, uint32_t color);
			void draw_line(Point p1, Point p2, uint8_t red, uint8_t green, uint8_t blue);
			void grid_draw_line(Point p1, Point p2, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
			void grid_draw_line(Point p1, Point p2, uint32_t color);
			void grid_draw_triangle(Triangle* triangle, float x, float y, float rotation);
			void grid_draw_polygon(Trianglelist* polygon, float x, float y, float rotation);
			//SDL_Texture* create_alphacircle(uint32_t width, uint32_t height, uint32_t color);
	};

	namespace grapher {
		bool init_fontsystem();
		void deinit_fontsystem();
		TTF_Font* load_font(const char* filename, int size);	// returns NULL if not successful
		SDL_Surface* load_surface(const char* filename);
		SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filename);
		SDL_Texture* create_textmultiline_texture(SDL_Renderer* renderer, std::string textline, TTF_Font *font, SDL_Color color);
		SDL_Texture* create_textline_texture(SDL_Renderer* renderer, std::string text, TTF_Font *font, SDL_Color color);
		bool colorfade(SDL_Renderer* renderer, SDL_Texture* &texture, uint32_t color);
		bool draw_text(SDL_Renderer* renderer, std::string text, TTF_Font *font, SDL_Color color, int x, int y);
		bool draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect);
		bool draw_texture(SDL_Renderer* renderer, Simplesprite* texture);
		bool draw_texture(SDL_Texture* texture, SDL_Rect rect, int width, int height);
		bool draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
		bool draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int scaled_width, int scaled_height);
		bool draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, Point location);
		bool draw_texture(SDL_Texture* texture, int x, int y, int width, int height);
		bool draw_texture(SDL_Renderer* renderer, Simplesprite &sprite);
		//void draw_hline(int x1, int x2, int y, uint32_t color);
		void draw_path(SDL_Renderer* renderer, Path* path, SDL_Color color);
		void grid_draw_triangle(SDL_Renderer* renderer, Triangle* triangle, Coordinategrid* grid);
		void grid_draw_polygon(SDL_Renderer* renderer, Trianglelist *polygon, Coordinategrid* grid);
		SDL_Texture* create_circle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color);
		SDL_Texture* create_solidcircle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color);
		SDL_Texture* create_alphacircle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color);
	}

	class Turtle {
		Path linepath;
		// TODO: turtle graphics pen to create paths etc.
		//void rotate(float angle);
		//void go_gorward(float amount);
		//void go_backward(float amount);
		//void jump_to(Point location);
	};

#endif // GRAPHER_HPP
