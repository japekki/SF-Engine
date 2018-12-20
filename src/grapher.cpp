#include <SDL_image.h>
#include "grapher.hpp"
#include "misc.hpp"
#include <math.h>

Layer::Layer() {
}

Layer::~Layer() {
}

Grapher::Grapher() {
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

void Grapher::set_grid(float x_min, float y_min, float x_max, float y_max) {
	this->grid.x_min = x_min;
	this->grid.x_max = x_max;
	this->grid.y_min = y_min;
	this->grid.y_max = y_max;
}

Point* Grapher::apply_grid(Point* coordinate) {
	Point* result = new Point();
	float aspect = float(this->width) / this->height;
	result->x = float(this->width) / (this->grid.x_max - this->grid.x_min) * coordinate->x + this->width/2;
	result->y = float(this->height) / (this->grid.y_max - this->grid.y_min)*aspect * coordinate->y + this->height/2;
	//if (this->grid->centered) {
	//	result.x *= this->width/2;
	//	result.y = this->height/2;
	//}
	return result;
}

SDL_Surface* Grapher::load_surface(const char* filename) {
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

SDL_Texture* Grapher::load_texture(const char* filename) {
	SDL_Texture *texture = nullptr;
	SDL_RWops *rwop;
		rwop = SDL_RWFromFile(filename, "rb");
		if (rwop != NULL) {
			SDL_Surface *temp = IMG_LoadPNG_RW(rwop);
			SDL_RWclose(rwop);
			texture = SDL_CreateTextureFromSurface(this->sdlrenderer, temp);
			SDL_FreeSurface(temp);
			if(!texture) {
				log("ERROR loading image file:");
				log(IMG_GetError());
			}
		} else
			log("ERROR opening image file.");
		return texture;
}

bool Grapher::init_fontsystem() {
	// INIT FONT SYSTEM:
		if(TTF_Init() == -1) {
			log("Error in TTF_Init:");
			log(TTF_GetError());
			this->works = false;
			exit(EXIT_FAILURE);	// TODO: Exception handling
		}
	return this->works;
}

void Grapher::deinit_fontsystem() {
	// DEINIT FONT SYSTEM:
		TTF_Quit();
}

TTF_Font* Grapher::load_font(const char* filename, int size) {
	TTF_Font *font = TTF_OpenFont(filename, size);
	if (font == NULL) {
		log("Error loading font:");
		log(filename);
		this->works = false;
	}
	return font;
}

SDL_Texture* Grapher::create_textline_texture(std::string textline, TTF_Font *font, SDL_Color color) {
	// Create a texture from one text line
		SDL_Surface *surface = TTF_RenderText_Blended(font, textline.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(this->sdlrenderer, surface);
		SDL_FreeSurface(surface);
	// Apply color fade:
		this->colorfade(texture, 0x909090);
		return texture;
}

SDL_Texture* Grapher::create_textmultiline_texture(std::string text, TTF_Font *font, SDL_Color color) {
	// Create one texture for all text lines
	// TODO: alignment, gap between lines, optimize
	unsigned int total_width = 0;
	unsigned int total_height = 0;
	std::vector<std::string> lines;
	lines = split(text, "\n");
	for (int unsigned i=0; i<lines.size(); i++) {
		// Create rect:
			SDL_Rect rect;
			// Set drawing start indexes to upper left corner:
				rect.x = 0;
				rect.y = 0;
			// Set width and height:
				TTF_SizeText(font, lines.at(i).c_str(), &rect.w, &rect.h);
		// Adjust texture size:
			if (rect.w > total_width) total_width = rect.w;
			total_height += rect.h;
	}
	// Create new texture for all the text:
		SDL_Texture *texture_all_text = SDL_CreateTexture(this->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, total_width, total_height);
		//SDL_SetTextureBlendMode(texture_all_text, SDL_BLENDMODE_MOD);
	// Write all text lines into texture:
		SDL_SetTextureBlendMode(texture_all_text, SDL_BLENDMODE_BLEND);	// Enable alpha
		// Clear possible garbage:
			SDL_SetRenderTarget(this->sdlrenderer, texture_all_text);
			SDL_SetRenderDrawColor(this->sdlrenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(this->sdlrenderer);
			//SDL_SetRenderTarget(this->sdlrenderer, NULL);
		SDL_Rect target_rect;
		target_rect.x = 0;
		target_rect.y = 0;

		for (int unsigned i=0; i<lines.size(); i++) {
				SDL_SetRenderTarget(this->sdlrenderer, NULL);
			// Create texture from one text line:
				SDL_Surface *surface = TTF_RenderText_Blended(font, lines.at(i).c_str(), color);
				SDL_Texture *texture_line = SDL_CreateTextureFromSurface(this->sdlrenderer, surface);
				SDL_FreeSurface(surface);
				this->colorfade(texture_line, 0x909090);

			// Blit text line texture to the big texture containing all lines:
				SDL_Rect text_rect;
				text_rect.x = 0;
				text_rect.y = 0;
				TTF_SizeText(font, lines.at(i).c_str(), &text_rect.w, &text_rect.h);
				target_rect.w = text_rect.w;
				target_rect.h = text_rect.h;

				SDL_SetRenderTarget(this->sdlrenderer, texture_all_text);
				SDL_RenderCopy(this->sdlrenderer, texture_line, &text_rect, &target_rect);
				SDL_DestroyTexture(texture_line);
				target_rect.y += text_rect.h;	// adjust Y for the next line
		}
		SDL_SetRenderTarget(this->sdlrenderer, NULL);	// Set rendering back to screen
	return texture_all_text;
}

bool Grapher::draw_text(std::string text, TTF_Font *font, SDL_Color color, int x, int y) {
	// Good for drawing text once, if same text is drawn in many frames, store texture with create_text_texture() and use draw_texture()
	SDL_Texture *texture = this->create_textmultiline_texture(text, font, color);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(this->sdlrenderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	return true;	// TODO
}

bool Grapher::draw_texture(SDL_Texture* texture, SDL_Rect rect) {
	SDL_RenderCopy(this->sdlrenderer, texture, NULL, &rect);
	return true;	// TODO
}

bool Grapher::draw_texture(Simplesprite* texture) {
	SDL_RenderCopy(this->sdlrenderer, texture->sdltexture, NULL, &texture->rect);
	return true;	// TODO
}

bool Grapher::draw_texture(Simplesprite &sprite) {
	SDL_RenderCopy(this->sdlrenderer, sprite.sdltexture, NULL, &sprite.rect);
	return true;	// TODO
}

bool Grapher::draw_texture(SDL_Texture* texture, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(this->sdlrenderer, texture, NULL, &rect);
	return true;	// TODO
}

bool Grapher::colorfade(SDL_Texture* &texture, Uint32 color) {
	// TODO: Try to render over original texture instead of creating texture_result
	// TODO: Horizontal/vertical fade
	// TODO: invert fading direction
	Uint32 *pixels;
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Create fader texture:
		SDL_Texture* texture_fader;
		SDL_Texture* texture_result;
		texture_fader = SDL_CreateTexture(this->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		texture_result = SDL_CreateTexture(this->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
		//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(texture_fader, SDL_BLENDMODE_ADD);
		SDL_SetTextureBlendMode(texture_result, SDL_BLENDMODE_BLEND);

	// Clear possible garbage:
		SDL_SetRenderTarget(this->sdlrenderer, texture_result);
		SDL_SetRenderDrawColor(this->sdlrenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(this->sdlrenderer);
		SDL_SetRenderTarget(this->sdlrenderer, NULL);

	// Draw fading pixels to texture:
		pixels = new Uint32[width * height];
			for (int y=0; y<height; y++) {
				for (int x=0; x<width; x++) {
					pixels[y*width + x] = ((255 - Uint32(255.0/height*y)) << 24) + color;
				}
			}
		SDL_UpdateTexture(texture_fader, NULL, pixels, width * sizeof(Uint32));

	// Blend fader texture with given texture:
		SDL_SetRenderTarget(this->sdlrenderer, texture_result);	// Set rendering to texture
		SDL_RenderCopy(this->sdlrenderer, texture, NULL, NULL);
		SDL_RenderCopy(this->sdlrenderer, texture_fader, NULL, NULL);
		SDL_SetRenderTarget(this->sdlrenderer, NULL);	// Set rendering back to screen
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(texture_fader);
		texture = texture_result;

	return true;	// TODO
}

void Grapher::draw_triangle(Triangle* triangle) {
	Point* v1 = triangle->vertexes.at(0);
	Point* v2 = triangle->vertexes.at(1);
	Point* v3 = triangle->vertexes.at(2);

	this->use_grid = true;
	if (this->use_grid) {
		v1 = apply_grid(v1);
		v2 = apply_grid(v2);
		v3 = apply_grid(v3);
	}

	Uint8 red, green, blue;
	red = (triangle->color & 0xff0000) >> 16;
	green = (triangle->color & 0xff00) >> 8;
	blue = triangle->color & 0xff;

	SDL_SetRenderDrawColor(this->sdlrenderer, red, green, blue, SDL_ALPHA_OPAQUE);
	switch(triangle->shadestyle) {
		case POLYGON_SHADESTYLE_POINT:
			SDL_RenderDrawPoint(this->sdlrenderer, v1->x, v1->y);
			SDL_RenderDrawPoint(this->sdlrenderer, v2->x, v2->y);
			SDL_RenderDrawPoint(this->sdlrenderer, v3->x, v3->y);
			break;
		case POLYGON_SHADESTYLE_WIREFRAME:
			SDL_RenderDrawLine(this->sdlrenderer, v1->x, v1->y, v2->x, v2->y);
			SDL_RenderDrawLine(this->sdlrenderer, v2->x, v2->y, v3->x, v3->y);
			SDL_RenderDrawLine(this->sdlrenderer, v3->x, v3->y, v1->x, v1->y);
			break;
		case POLYGON_SHADESTYLE_SINGLE:
			// Sort a.y > b.y > c.y :
				Point* tmp;
				if (v3->y < v2->y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}
				if (v2->y < v1->y) {
					tmp = v1;
					v1 = v2;
					v2 = tmp;
				}
				if (v3->y < v2->y) {
					tmp = v2;
					v2 = v3;
					v3 = tmp;
				}

			// Slopes for sides:
				float k_ab = 0;
				float k_ac = 0;
				float k_bc = 0;

				if (v2->y != v1->y)
					k_ab = (v2->x-v1->x) / (v2->y-v1->y);
				if (v3->y != v1->y)
					k_ac = (v3->x-v1->x) / (v3->y-v1->y);
				if (v3->y != v2->y)
					k_bc = (v3->x-v2->x) / (v3->y-v2->y);

			float left = v1->x;
			float right = v1->x;

			// Draw upper part ABD:
				for (int i=round(v1->y); i<round(v2->y); i++) {

						//draw_hline(left, right, i, v1.colorint(sdlsurface), sdlsurface);
						//draw_hline_gouraud(left, right, i, v1.colorint(sdlsurface), grid, sdlsurface);

					left = left + k_ab;
					right = right + k_ac;
				}

			// Draw lower part BCD:
				for (int i=round(v2->y); i<round(v3->y); i++) {
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
	SDL_SetRenderDrawColor(this->sdlrenderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Grapher::draw_polygon(Polygon* polygon) {
	for (int unsigned i=0; i<polygon->triangles.size(); i++)
		this->draw_triangle(polygon->triangles.at(i));
}

SDL_Texture* create_alphacircle(Grapher *grapher, Uint32 color) {
	Uint32 *pixels;
	pixels = new Uint32[grapher->width * grapher->height];
	SDL_Texture* sdltexture;
	sdltexture = SDL_CreateTexture(grapher->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, grapher->width, grapher->height);
	Uint32 max_radius;
	// Get maximum radius for the circle to touch any edge of the texture:
		if (grapher->height > grapher->width)
			max_radius = grapher->width/2;
		else
			max_radius = grapher->height/2;
	// Generate alpha circle:
		for (int y=0; y < grapher->height; y++) {
			for (int x=0; x < grapher->width; x++) {
				Uint32 radius = 255.0 / max_radius * sqrt( pow(y - grapher->height/2.0 ,2) + pow(x - grapher->width/2.0 ,2));
				if (radius > 255)
					pixels[y * grapher->width + x] = (255 << 24) + color;
				else
					pixels[y * grapher->width + x] = (radius << 24) + color;
			}
		}
	SDL_SetTextureBlendMode(sdltexture, SDL_BLENDMODE_BLEND);	// Enable alpha
	SDL_UpdateTexture(sdltexture, NULL, pixels, grapher->width * sizeof(Uint32));
	return sdltexture;
}
