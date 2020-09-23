/*
	Creates separate textures for text lines.
	If individual text lines do not need to move dynamically, use Grapher class text and scroller routines instead.
*/

/*
TODO:
- Font, color and size changing within text
- Background color
- Alpha
- Color shading
- Some or all text lines into one texture
- Different scrolling styles (static, line gap weaver, Star Wars)
*/

#ifndef EFFUX_TEXTSCROLLER_HPP
	#define EFFUX_TEXTSCROLLER_HPP

	#define TEXTALIGN_LEFT 0
	#define TEXTALIGN_CENTER 1
	#define TEXTALIGN_RIGHT 2

	#define SCROLLSTYLE_NONE 0
	#define SCROLLSTYLE_EQUAL 1			// Same gap between all the lines
	#define SCROLLSTYLE_DENSE_CENTER 2	// Alter gaps between lines so denser in the middle and sparser if far from middle
	#define SCROLLSTYLE_FADEFLASH 3		// Line by line with fade in/out

	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <vector>
	#include <string>
	#include "effux.hpp"

	// Forward declarations:
		class Grapher;
		class Simplesprite;

	class EffuxTextscroller : public Effux {
		private:
			TTF_Font* font = nullptr;
			SDL_Color color = {255, 255, 255};	// White by default
			std::vector<Simplesprite*> textboxes;
		public:
			bool works = true;	// Change to false if something goes wrong
			uint16_t width = 0;
			uint16_t height = 0;
			unsigned char alignment = TEXTALIGN_LEFT;
			unsigned char scrollstyle = SCROLLSTYLE_NONE;
			void setup(SDL_Renderer* renderer, uint16_t width, uint16_t height, TTF_Font *font, unsigned char alignment, unsigned char scrollstyle, SDL_Color color, std::string text);
			//EffuxTextscroller();
			~EffuxTextscroller();
			bool write(std::string text);	// Separated by newline "\n"
			void set_color(SDL_Color color);
			int get_width();	// Width of the longest text line's texture
			int get_height();	// Total height of all text line textures
			void execute(uint32_t time);
	};

#endif // EFFUX_TEXTSCROLLER_HPP
