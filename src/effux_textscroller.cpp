#include "effux_textscroller.hpp"
#include <math.h>
#include "misc.hpp"
#include "grapher.hpp"

EffuxTextscroller::EffuxTextscroller(Grapher *grapher) {
}

EffuxTextscroller::EffuxTextscroller(Grapher *grapher, TTF_Font *font, unsigned char alignment, unsigned char scrollstyle, SDL_Color color, std::string text) {
	this->width = grapher->width;
	this->height = grapher->height;
	this->grapher = grapher;
	this->alignment = alignment;
	this->scrollstyle = scrollstyle;
	this->set_color(color);
	this->font = font;
	this->write(text);
}

EffuxTextscroller::~EffuxTextscroller() {
	for (unsigned int i=0; i<this->textboxes.size(); i++) {
		SDL_DestroyTexture(this->textboxes.at(i)->sdltexture);
	}
	this->textboxes.clear();
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
		for (unsigned int i=0; i<lines.size(); i++) {
			SDL_Texture *texture = this->grapher->create_textline_texture(lines.at(i), this->font, this->color);

		// Create rect:
			SDL_Rect rect;
			// Set drawing start indexes to upper left corner:
				rect.x = 0;
				rect.y = 0;
			// Set width and height:
				TTF_SizeText(this->font, lines.at(i).c_str(), &rect.w, &rect.h);

		// Create textbox and add it to stash:
			Simplesprite* box = new Simplesprite();
			box->sdltexture = texture;
			box->rect = rect;
			this->textboxes.push_back(box);
		}

	return this->works;	// TODO
}

unsigned int EffuxTextscroller::get_width() {
	unsigned int longest_width = 0;
	for (unsigned int i=0; i<this->textboxes.size(); i++)
		if (this->textboxes.at(i)->rect.w > longest_width)
			longest_width = this->textboxes.at(i)->rect.w;
	return longest_width;
}

unsigned int EffuxTextscroller::get_height() {
	unsigned int total_height = 0;
	for (unsigned int i=0; i<this->textboxes.size(); i++)
		total_height += this->textboxes.at(i)->rect.h;
	return total_height;
}

bool EffuxTextscroller::draw(short scroll_position) {
	// TODO:
	// - scale every line equally to grapher width so that the longest line will fit to screen
	// - scrolling styles
	unsigned short total_height = 0;	// Added to each text line's Y
	for (unsigned int i=0; i<this->textboxes.size(); i++) {
		SDL_Rect rect;
		// SET TEXT ALIGNMENT:
			if (this->alignment == TEXTALIGN_LEFT)
				rect.x = 0;
			else if (this->alignment == TEXTALIGN_CENTER)
				rect.x = (this->grapher->width - this->textboxes.at(i)->rect.w) / 2;
			else if (this->alignment == TEXTALIGN_RIGHT)
				rect.x = this->grapher->width - this->textboxes.at(i)->rect.w;
		// SET TEXT SCROLL STYLE:
			if (this->scrollstyle == SCROLLSTYLE_EQUAL)
				rect.y = scroll_position + total_height;
			else if (this->scrollstyle == SCROLLSTYLE_FADEFLASH)
				rect.y = scroll_position + total_height;	// TODO
			else if (this->scrollstyle == SCROLLSTYLE_DENSE_CENTER)
				rect.y = scroll_position + total_height;	// TODO
		rect.w = this->textboxes.at(i)->rect.w;
		rect.h = this->textboxes.at(i)->rect.h;
		SDL_RenderCopy(this->grapher->sdlrenderer, this->textboxes.at(i)->sdltexture, &this->textboxes.at(i)->rect, &rect);
		total_height += this->textboxes.at(i)->rect.h;
	}
	return this->works;	// TODO
}
