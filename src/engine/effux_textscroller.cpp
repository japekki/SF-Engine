#include "effux_textscroller.hpp"
#include <math.h>
#include "misc.hpp"
#include "grapher.hpp"

//EffuxTextscroller::EffuxTextscroller() {
//}

void EffuxTextscroller::setup(SDL_Renderer* renderer, uint16_t width, uint16_t height, TTF_Font *font, unsigned char alignment, unsigned char scrollstyle, SDL_Color color, std::string text) {
	// Clear old text:
	for (uint32_t i=0; i<textboxes.size(); i++) {
		SDL_DestroyTexture(textboxes[i]->texture);
	}
	textboxes.clear();

	this->renderer = renderer;
	this->width = width;
	this->height = height;
	this->alignment = alignment;
	this->scrollstyle = scrollstyle;
	this->set_color(color);
	this->font = font;
	this->write(text);
}

EffuxTextscroller::~EffuxTextscroller() {
	for (uint32_t i=0; i<textboxes.size(); i++) {
		SDL_DestroyTexture(textboxes[i]->texture);
	}
	textboxes.clear();
}

void EffuxTextscroller::set_color(SDL_Color color) {
	this->color = color;
}

bool EffuxTextscroller::write(std::string text) {
	// Appends text to previous
	// TODO:
	// - removing and altering previous text
	// - don't create or draw textures for empty lines, just alter rects

	// Create textures for text lines:
		std::vector<std::string> lines;
		lines = split(text, "\n");
		for (uint32_t i=0; i<lines.size(); i++) {
			SDL_Texture *texture = grapher::create_textline_texture(renderer, lines[i], font, color);

		// Create rect:
			SDL_Rect rect;
			// Set drawing start indexes to upper left corner:
				rect.x = 0;
				rect.y = 0;
			// Set width and height:
				TTF_SizeText(font, lines[i].c_str(), &rect.w, &rect.h);

		// Create textbox and add it to stash:
			Simplesprite* box = new Simplesprite();
			box->texture = texture;
			box->rect = rect;
			textboxes.push_back(box);
		}

	return this->works;	// TODO
}

int EffuxTextscroller::get_width() {
	int longest_width = 0;
	for (uint32_t i=0; i<textboxes.size(); i++)
		if (textboxes[i]->rect.w > longest_width)
			longest_width = textboxes[i]->rect.w;
	return longest_width;
}

int EffuxTextscroller::get_height() {
	int total_height = 0;
	for (uint32_t i=0; i<textboxes.size(); i++)
		total_height += textboxes[i]->rect.h;
	return total_height;
}

void EffuxTextscroller::execute(uint32_t time) {
	// TODO:
	// - scale every line equally to grapher width so that the longest line will fit to screen
	// - scrolling styles
	uint16_t total_height = 0;	// Added to each text line's Y
	for (uint32_t i=0; i<textboxes.size(); i++) {
		SDL_Rect rect;

		// SET TEXT ALIGNMENT:
			if (alignment == TEXTALIGN_LEFT)
				rect.x = 0;
			else if (alignment == TEXTALIGN_CENTER)
				rect.x = (width - textboxes[i]->rect.w) / 2;
			else if (alignment == TEXTALIGN_RIGHT)
				rect.x = width - textboxes[i]->rect.w;

		// SET TEXT SCROLL STYLE:
			if (scrollstyle == SCROLLSTYLE_EQUAL)
				rect.y = time + total_height;
			else if (scrollstyle == SCROLLSTYLE_FADEFLASH)
				rect.y = time + total_height;	// TODO
			else if (scrollstyle == SCROLLSTYLE_DENSE_CENTER)
				rect.y = time + total_height;	// TODO
		rect.w = textboxes[i]->rect.w;
		rect.h = textboxes[i]->rect.h;
		SDL_RenderCopy(renderer, textboxes[i]->texture, &textboxes[i]->rect, &rect);
		total_height += textboxes[i]->rect.h;
	}
}
