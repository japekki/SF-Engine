#include <SDL_image.h>
//#include "SDL2_gfxPrimitives.h"
#include "grapher.hpp"
#include "misc.hpp"
#include <math.h>

Simplesprite::Simplesprite() {
}

Simplesprite::Simplesprite(SDL_Texture* texture) {
	this->texture = texture;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

Simplesprite::~Simplesprite() {
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

Layer::Layer() {
}

Layer::~Layer() {
}

/*
TODO:
- newlines with TTF_RenderText_Blended_Wrapped
void Grapher::scroll() {
	// DRAW SCROLLER:
		// FOR SCROLLING ONCE OVER SCREEN/TEXTURE:
			// When scroll starts, y needs to be display height
			// When y is 0, text touches screen top edge
			// When scroll ends, y needs to be: - text_height
}
*/

Grapher::Grapher() {
}

Grapher::~Grapher() {
	//log("Grapher::~Grapher()");
}

bool Grapher::draw_text(std::string text, TTF_Font *font, SDL_Color color, int x, int y) {
	// TODO: Optimize:
	// - don't recreate texture each time
	// - combine all texts into single texture
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    return true;	// TODO

}

bool Grapher::draw_texture(SDL_Texture* texture, SDL_Rect rect) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

bool Grapher::draw_texture(Simplesprite* texture) {
	SDL_RenderCopy(renderer, texture->texture, NULL, &texture->rect);
	return true;	// TODO
}

bool Grapher::draw_texture(Simplesprite &sprite) {
	SDL_RenderCopy(renderer, sprite.texture, NULL, &sprite.rect);
	return true;	// TODO
}

bool Grapher::draw_texture(SDL_Texture* texture, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

bool Grapher::draw_texture(SDL_Texture* texture, Point location) {
	SDL_Rect rect;
	rect.x = location.x;
	rect.y = location.y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

void Grapher::grid_draw_triangle(Triangle* triangle, float x, float y, float rotation) {
	Point v1 = triangle->vertexes[0];
		v1.rotate(rotation);
		v1.x += x;
		v1.y += y;
	Point v2 = triangle->vertexes[1];
		v2.rotate(rotation);
		v2.x += x;
		v2.y += y;
	Point v3 = triangle->vertexes[2];
		v3.rotate(rotation);
		v3.x += x;
		v3.y += y;

	uint8_t red, green, blue;
	red = (triangle->color & 0xff0000) >> 16;
	green = (triangle->color & 0xff00) >> 8;
	blue = triangle->color & 0xff;

	//SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);

	switch(triangle->shadestyle) {
		case POLYGON_SHADESTYLE_POINT:
			SDL_RenderDrawPoint(renderer, v1.x, v1.y);
			SDL_RenderDrawPoint(renderer, v2.x, v2.y);
			SDL_RenderDrawPoint(renderer, v3.x, v3.y);
			break;
		case POLYGON_SHADESTYLE_WIREFRAME:
			grid_draw_line(v1, v2, red, green, blue, SDL_ALPHA_OPAQUE);
			grid_draw_line(v2, v3, red, green, blue, SDL_ALPHA_OPAQUE);
			grid_draw_line(v3, v1, red, green, blue, SDL_ALPHA_OPAQUE);

			//v1 = grid.transform(v1);
			//v2 = grid.transform(v2);
			//v3 = grid.transform(v3);

			//thickLineRGBA(renderer, v1.x, v1.y, v2.x, v2.y, 2, red, green, blue, SDL_ALPHA_OPAQUE);
			//thickLineRGBA(renderer, v2.x, v2.y, v3.x, v3.y, 2, red, green, blue, SDL_ALPHA_OPAQUE);
			//thickLineRGBA(renderer, v3.x, v3.y, v1.x, v1.y, 2, red, green, blue, SDL_ALPHA_OPAQUE);

			//aalineRGBA(renderer, v1.x, v1.y, v2.x, v2.y, red, green, blue, SDL_ALPHA_OPAQUE);
			//aalineRGBA(renderer, v2.x, v2.y, v3.x, v3.y, red, green, blue, SDL_ALPHA_OPAQUE);
			//aalineRGBA(renderer, v3.x, v3.y, v1.x, v1.y, red, green, blue, SDL_ALPHA_OPAQUE);

			break;
		case POLYGON_SHADESTYLE_SINGLE:
			// Sort a.y > b.y > c.y :
				Point tmp;
				if (v3.y < v2.y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}
				if (v2.y < v1.y) {
					tmp = v1;
					v1 = v2;
					v2 = tmp;
				}
				if (v3.y < v2.y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}

			// Slopes for sides:
				float k_ab = 0;
				float k_ac = 0;
				float k_bc = 0;

				if (v2.y != v1.y)
					k_ab = (v2.x - v1.x) / (v2.y - v1.y);
				if (v3.y != v1.y)
					k_ac = (v3.x - v1.x) / (v3.y - v1.y);
				if (v3.y != v2.y)
					k_bc = (v3.x - v2.x) / (v3.y - v2.y);

			float left = v1.x;
			float right = v1.x;

			// Draw upper part ABD:
				for (int i=round(v1.y); i<round(v2.y); i++) {
						//draw_hline(left, right, i, v1.colorint(sdlsurface), sdlsurface);
						//draw_hline_gouraud(left, right, i, v1.colorint(sdlsurface), grid, sdlsurface);
						this->grid_draw_line(Point(left, i), Point(right, i), triangle->color);

					left = left + k_ab;
					right = right + k_ac;
				}

			// Draw lower part BCD:
				for (int i=round(v2.y); i<round(v3.y); i++) {
					//if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					this->grid_draw_line(Point(left, i), Point(right, i), triangle->color);
					//}
					//else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
					//}
					left = left + k_bc;
					right = right + k_ac;
				}

			break;
	}
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Grapher::grid_draw_polygon(Trianglelist* polygon, float x, float y, float rotation) {
	for (uint32_t i=0; i<polygon->triangles.size(); i++)
		this->grid_draw_triangle(polygon->triangles[i], x, y, rotation);
}

SDL_Surface* grapher::load_surface(const char* filename) {
	SDL_Surface *surface = nullptr;
	SDL_RWops *rwop;
	rwop = SDL_RWFromFile(filename, "rb");
	if (rwop != NULL) {
		surface = IMG_LoadPNG_RW(rwop);
		SDL_RWclose(rwop);
	} else
		log("ERROR opening image file.");
	return surface;
}

SDL_Texture* grapher::load_texture(SDL_Renderer* renderer, const char* filename) {
	SDL_Texture *texture = nullptr;
	SDL_RWops *rwop;
		rwop = SDL_RWFromFile(filename, "rb");
		if (rwop != NULL) {
			SDL_Surface *temp = IMG_LoadPNG_RW(rwop);
			SDL_RWclose(rwop);
			texture = SDL_CreateTextureFromSurface(renderer, temp);
			SDL_FreeSurface(temp);
			if(!texture) {
				log("ERROR loading image file:");
				log(IMG_GetError());
			}
		} else
			log("ERROR opening image file.");
		return texture;
}

SDL_Texture* grapher::create_textline_texture(SDL_Renderer* renderer, std::string textline, TTF_Font *font, SDL_Color color) {
	// Create a texture from one text line
		SDL_Surface *surface = TTF_RenderText_Blended(font, textline.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	// Apply color fade:
		grapher::colorfade(renderer, texture, 0x909090);
		return texture;
}

SDL_Texture* grapher::create_textmultiline_texture(SDL_Renderer* renderer, std::string text, TTF_Font *font, SDL_Color color) {
	// Create one texture for all text lines
	// TODO: alignment, gap between lines, optimize
	// FIXME: crashes if multiple newline characters in a row (empty lines)
	uint32_t total_width = 0;
	uint32_t total_height = 0;
	std::vector<std::string> lines;
	lines = split(text, "\n");
	for (uint32_t i=0; i<lines.size(); i++) {
		// Create rect:
			SDL_Rect rect;
			// Set drawing start indexes to upper left corner:
				rect.x = 0;
				rect.y = 0;
			// Set width and height:
				TTF_SizeText(font, lines[i].c_str(), &rect.w, &rect.h);
		// Adjust texture size:
			if (rect.w > total_width)
				total_width = rect.w;
			total_height += rect.h;
	}
	// Create new texture for all the text:
		SDL_Texture *texture_all_text = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, total_width, total_height);
		//SDL_SetTextureBlendMode(texture_all_text, SDL_BLENDMODE_MOD);
	// Write all text lines into texture:
		SDL_SetTextureBlendMode(texture_all_text, SDL_BLENDMODE_BLEND);	// Enable alpha
		// Clear possible garbage:
			SDL_SetRenderTarget(renderer, texture_all_text);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(renderer);
			//SDL_SetRenderTarget(renderer, NULL);
		SDL_Rect target_rect;
		target_rect.x = 0;
		target_rect.y = 0;

		for (uint32_t i=0; i<lines.size(); i++) {
				SDL_SetRenderTarget(renderer, NULL);
			// Create texture from one text line:
				SDL_Surface *surface = TTF_RenderText_Blended(font, lines[i].c_str(), color);
				SDL_Texture *texture_line = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
				grapher::colorfade(renderer, texture_line, 0x909090);

			// Blit text line texture to the big texture containing all lines:
				SDL_Rect text_rect;
				text_rect.x = 0;
				text_rect.y = 0;
				TTF_SizeText(font, lines[i].c_str(), &text_rect.w, &text_rect.h);
				target_rect.w = text_rect.w;
				target_rect.h = text_rect.h;

				SDL_SetRenderTarget(renderer, texture_all_text);
				SDL_RenderCopy(renderer, texture_line, &text_rect, &target_rect);
				SDL_DestroyTexture(texture_line);
				target_rect.y += text_rect.h;	// adjust Y for the next line
		}
		SDL_SetRenderTarget(renderer, NULL);	// Set rendering back to screen
	return texture_all_text;
}

bool grapher::draw_text(SDL_Renderer* renderer, std::string text, TTF_Font *font, SDL_Color color, int x, int y) {
	// Good for drawing text once, if same text is drawn in many frames, store texture with create_text_texture() and use draw_texture()
	SDL_Texture *texture = grapher::create_textmultiline_texture(renderer, text, font, color);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, Simplesprite* texture) {
	SDL_RenderCopy(renderer, texture->texture, NULL, &texture->rect);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, Simplesprite &sprite) {
	SDL_RenderCopy(renderer, sprite.texture, NULL, &sprite.rect);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int scaled_width, int scaled_height) {
	SDL_Rect rect_dst;
	rect_dst.w = scaled_width;
	rect_dst.h = scaled_height;
	rect_dst.x = x;
	rect_dst.y = y;
	//SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect_dst);
	return true;	// TODO
}

bool grapher::draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, Point location) {
	SDL_Rect rect;
	rect.x = location.x;
	rect.y = location.y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	return true;	// TODO
}

bool grapher::colorfade(SDL_Renderer* renderer, SDL_Texture* &texture, uint32_t color) {
	// TODO: Try to render over original texture instead of creating texture_result
	// TODO: Horizontal/vertical fade
	// TODO: invert fading direction
	uint32_t *pixels;
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Create fader texture:
		SDL_Texture* texture_fader;
		SDL_Texture* texture_result;
		texture_fader = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
		texture_result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
		//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(texture_fader, SDL_BLENDMODE_ADD);
		SDL_SetTextureBlendMode(texture_result, SDL_BLENDMODE_BLEND);

	// Clear possible garbage:
		SDL_SetRenderTarget(renderer, texture_result);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, NULL);

	// Draw fading pixels to texture:
		pixels = new uint32_t[width * height];
			for (int y=0; y<height; y++) {
				for (int x=0; x<width; x++) {
					pixels[y*width + x] = ((255 - uint32_t(255.0/height*y)) << 24) + color;
				}
			}
		SDL_UpdateTexture(texture_fader, NULL, pixels, width * sizeof(uint32_t));

	// Blend fader texture with given texture:
		SDL_SetRenderTarget(renderer, texture_result);	// Set rendering to texture
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderCopy(renderer, texture_fader, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);	// Set rendering back to screen
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(texture_fader);
		texture = texture_result;

	return true;	// TODO
}
void Grapher::draw_line(Point p1, Point p2, uint8_t red, uint8_t green, uint8_t blue) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void Grapher::grid_draw_line(Point p1, Point p2, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	p1 = grid.transform(p1);
	p2 = grid.transform(p2);
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	//thickLineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, 2, red, green, blue, SDL_ALPHA_OPAQUE);
	//aalineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, red, green, blue, 128);
}

void Grapher::grid_draw_line(Point p1, Point p2, uint32_t color) {
	p1 = grid.transform(p1);
	p2 = grid.transform(p2);
	uint8_t red = (color & 0xff0000) >> 16;
	uint8_t green = (color & 0xff00) >> 8;
	uint8_t blue = color & 0xff;
	uint8_t alpha = (color & 0xff000000) >> 24;
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	//thickLineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, 2, red, green, blue, SDL_ALPHA_OPAQUE);
	//aalineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, red, green, blue, 128);
}

void grapher::grid_draw_triangle(SDL_Renderer* renderer, Triangle* triangle, Coordinategrid* grid) {
	Point v1 = triangle->vertexes[0];
	Point v2 = triangle->vertexes[1];
	Point v3 = triangle->vertexes[2];
		//v1 = grid->apply(v1);
		//v2 = grid->apply(v2);
		//v3 = grid->apply(v3);

	uint8_t red, green, blue;
	red = (triangle->color & 0xff0000) >> 16;
	green = (triangle->color & 0xff00) >> 8;
	blue = triangle->color & 0xff;

	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	switch(triangle->shadestyle) {
		case POLYGON_SHADESTYLE_POINT:
			SDL_RenderDrawPoint(renderer, v1.x, v1.y);
			SDL_RenderDrawPoint(renderer, v2.x, v2.y);
			SDL_RenderDrawPoint(renderer, v3.x, v3.y);
			break;
		case POLYGON_SHADESTYLE_WIREFRAME:
			SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
			SDL_RenderDrawLine(renderer, v2.x, v2.y, v3.x, v3.y);
			SDL_RenderDrawLine(renderer, v3.x, v3.y, v1.x, v1.y);
			break;
		case POLYGON_SHADESTYLE_SINGLE:
			// Sort a.y > b.y > c.y :
				Point tmp;
				if (v3.y < v2.y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}
				if (v2.y < v1.y) {
					tmp = v1;
					v1 = v2;
					v2 = tmp;
				}
				if (v3.y < v2.y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}

			// Slopes for sides:
				float k_ab = 0;
				float k_ac = 0;
				float k_bc = 0;

				if (v2.y != v1.y)
					k_ab = (v2.x - v1.x) / (v2.y - v1.y);
				if (v3.y != v1.y)
					k_ac = (v3.x - v1.x) / (v3.y - v1.y);
				if (v3.y != v2.y)
					k_bc = (v3.x - v2.x) / (v3.y - v2.y);

			float left = v1.x;
			float right = v1.x;

			// Draw upper part ABD:
				for (int i=round(v1.y); i<round(v2.y); i++) {

						//draw_hline(left, right, i, v1.colorint(sdlsurface), sdlsurface);
						//draw_hline_gouraud(left, right, i, v1.colorint(sdlsurface), grid, sdlsurface);

					left = left + k_ab;
					right = right + k_ac;
				}

			// Draw lower part BCD:
				for (int i=round(v2.y); i<round(v3.y); i++) {
					//if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					//	draw_hline(left, right, i, v1.colorint(sdlsurface), sdlsurface);
					//}
					//else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
					//}
					//left = left + k_bc;
					//right = right + k_ac;
				}

			break;
	}
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void grapher::draw_path(SDL_Renderer* renderer, Path* path, SDL_Color color) {
	for (uint32_t i = 1; i < path->get_length(); i++) {
		Point p1 = path->points[i-1];
		Point p2 = path->points[i];
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	}
}

void grapher::grid_draw_polygon(SDL_Renderer* renderer, Trianglelist* polygon, Coordinategrid* grid) {
	for (uint32_t i=0; i<polygon->triangles.size(); i++)
		grapher::grid_draw_triangle(renderer, polygon->triangles[i], grid);
}

SDL_Texture* grapher::create_circle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color) {
	return nullptr;	// TODO
}

SDL_Texture* grapher::create_solidcircle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color) {
	uint32_t *pixels;
	pixels = new uint32_t[width * height];
	SDL_Texture* texture;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	// Clear possible garbage:
		//SDL_SetRenderTarget(renderer, texture);
		//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderClear(renderer);
		//SDL_SetRenderTarget(renderer, NULL);

	uint32_t max_radius;

	// Get maximum radius for the circle to touch any edge of the texture:
		if (height > width)
			max_radius = width/2;
		else
			max_radius = height/2;

	for (uint32_t y=0; y < height; y++) {
		for (uint32_t x=0; x < width; x++) {
			if (sqrt( pow(y - height/2.0 ,2) + pow(x - width/2.0 ,2)) < max_radius)
				pixels[y * width + x] = color;
			else
				pixels[y * width + x] = 0xff000000;
		}
	}
	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
	return texture;
}

SDL_Texture* grapher::create_alphacircle(SDL_Renderer* renderer, uint32_t width, uint32_t height, uint32_t color) {
	uint32_t *pixels;
	pixels = new uint32_t[width * height];
	SDL_Texture* texture;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	uint32_t max_radius;
	// Get maximum radius for the circle to touch any edge of the texture:
		if (height > width)
			max_radius = width/2;
		else
			max_radius = height/2;
	// Generate alpha circle:
		for (uint32_t y=0; y < height; y++) {
			for (uint32_t x=0; x < width; x++) {
				uint32_t radius = 255.0 / max_radius * sqrt( pow(y - height/2.0 ,2) + pow(x - width/2.0 ,2));
				if (radius > 255) radius = 255;
				pixels[y * width + x] = (radius << 24) + color;
			}
		}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);	// Enable alpha
	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
	return texture;
}

bool grapher::init_fontsystem() {
	bool works = true;	// Change to false if something goes wrong
	// INIT FONT SYSTEM:
		if(TTF_Init() == -1) {
			log("Error in TTF_Init:");
			log(TTF_GetError());
			works = false;
			exit(EXIT_FAILURE);	// TODO: Exception handling
		}
	return works;
}

void grapher::deinit_fontsystem() {
	// DEINIT FONT SYSTEM:
		TTF_Quit();
}

TTF_Font* grapher::load_font(const char* filename, int size) {
	TTF_Font *font = TTF_OpenFont(filename, size);
	if (font == NULL) {
		log("Error loading font:");
		log(filename);
	}
	return font;
}
