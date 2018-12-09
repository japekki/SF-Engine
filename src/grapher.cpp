#include <SDL_image.h>
#include "grapher.hpp"
#include "misc.hpp"
#include <math.h>

SDL_Texture* Grapher::load_imagefile(const char* filename) {
	SDL_Texture *texture;
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
		} else {
			log("ERROR opening image file.");
		}
		return texture;
}

TTF_Font* Grapher::load_font(const char* filename, int size) {
	TTF_Font *font = TTF_OpenFont(filename, size);
	if (font == NULL) {
		log("Error loading font.");
		this->works = false;
	}
}

/*
TODO:
void Grapher::scroll() {
	// DRAW SCROLLER:
		// FOR SCROLLING ONCE OVER SCREEN/TEXTURE:
			// When scroll starts, y needs to be display height
			// When y is 0, text touches screen top edge
			// When scroll ends, y needs to be: - text_height
}
*/

SDL_Texture* Grapher::create_textline_texture(std::string textline, TTF_Font *font, SDL_Color color) {
	// Create a texture from one text line
	SDL_Surface *surface = TTF_RenderText_Solid(font, textline.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->sdlrenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* Grapher::create_textmultiline_texture(std::string text, TTF_Font *font, SDL_Color color) {
	// Create one texture for all text lines
	// TODO: alignment, gap between lines, optimize
	// FIXME: Background is not transparent
	unsigned int total_width = 0;
	unsigned int total_height = 0;
	std::vector<std::string> lines;
	lines = split(text, "\n");
	for (int i=0; i<lines.size(); i++) {
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
		SDL_SetTextureBlendMode(texture_all_text, SDL_BLENDMODE_BLEND);	// Enable alpha
	// Write all text lines into texture:
		SDL_SetRenderTarget(this->sdlrenderer, texture_all_text);	// Set rendering to texture
		SDL_Rect target_rect;
		target_rect.x = 0;
		target_rect.y = 0;
		//target_rect.w = 0;
		//target_rect.h = 0;
		for (int i=0; i<lines.size(); i++) {
			// Create texture from one text line:
				SDL_Surface *surface = TTF_RenderText_Solid(font, lines.at(i).c_str(), color);
				SDL_Texture *texture_line = SDL_CreateTextureFromSurface(this->sdlrenderer, surface);
				SDL_FreeSurface(surface);
			// Blit text line texture to the big texture containing all lines:
				SDL_Rect text_rect;
				text_rect.x = 0;
				text_rect.y = 0;
				TTF_SizeText(font, lines.at(i).c_str(), &text_rect.w, &text_rect.h);
				target_rect.w = text_rect.w;
				target_rect.h = text_rect.h;
				//SDL_SetTextureBlendMode(texture_line, SDL_BLENDMODE_BLEND);	// Enable alpha
				SDL_RenderCopy(this->sdlrenderer, texture_line, &text_rect, &target_rect);
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

bool Grapher::draw_texture(simplesprite &sprite) {
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

void Grapher::draw_triangle(Triangle2D *triangle) {
	// Points:
		//this->draw_pixel(triangle->vertexes[0]->x, triangle->vertexes[0]->y, 0xffff00);
		//this->draw_pixel(triangle->vertexes[1]->x, triangle->vertexes[1]->y, 0xffff00);
		//this->draw_pixel(triangle->vertexes[2]->x, triangle->vertexes[2]->y, 0xffff00);
	// Lines:
		SDL_SetRenderDrawColor(this->sdlrenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(this->sdlrenderer, triangle->vertexes[0].x, triangle->vertexes[0].y, triangle->vertexes[1].x, triangle->vertexes[1].y);
		SDL_RenderDrawLine(this->sdlrenderer, triangle->vertexes[1].x, triangle->vertexes[1].y, triangle->vertexes[2].x, triangle->vertexes[2].y);
		SDL_RenderDrawLine(this->sdlrenderer, triangle->vertexes[2].x, triangle->vertexes[2].y, triangle->vertexes[0].x, triangle->vertexes[0].y);
	/*
	switch(shadestyle) {
		case POLYGON_SHADESTYLE_POINT:
			draw_pixel(tr.a.x, tr.a.y, tr.a.colorint(sdlsurface), sdlsurface);
			draw_pixel(tr.b.x, tr.b.y, tr.b.colorint(sdlsurface), sdlsurface);
			draw_pixel(tr.c.x, tr.c.y, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		case POLYGON_SHADESTYLE_WIREFRAME:
			draw_line(tr.a.x, tr.a.y, tr.b.x, tr.b.y, 3, tr.a.colorint(sdlsurface), sdlsurface);
			draw_line(tr.b.x, tr.b.y, tr.c.x, tr.c.y, 3, tr.b.colorint(sdlsurface), sdlsurface);
			draw_line(tr.c.x, tr.c.y, tr.a.x, tr.a.y, 3, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		case POLYGON_SHADESTYLE_SINGLE:
			// TODO:
			//Sort a.y > b.y > c.y :
			Vertex2d tmp;
			if (tr.c.y < tr.b.y) {
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}
			if (tr.b.y < tr.a.y) {
				tmp = tr.a;
				tr.a = tr.b;
				tr.b = tmp;
			}
			// ??

			if (tr.c.y < tr.b.y) {
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}

			// Slopes for sides:
			float k_ab, k_ac, k_bc;

			if (tr.b.y != tr.a.y) {k_ab = (tr.b.x-tr.a.x) / (tr.b.y-tr.a.y);}
			if (tr.c.y != tr.a.y) {k_ac = (tr.c.x-tr.a.x) / (tr.c.y-tr.a.y);}
			if (tr.c.y != tr.b.y) {k_bc = (tr.c.x-tr.b.x) / (tr.c.y-tr.b.y);}

			float left = tr.a.x;
			float right = tr.a.x;
			// Draw upper part ABD:
			for (int i=round(tr.a.y); i<round(tr.b.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
					//draw_hline_gouraud(left, right, i, tr.a.colorint(sdlsurface), coordinategrid, sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
				left = left + k_ab;
				right = right + k_ac;
			}
			// Draw lower part BCD:
			for (int i=round(tr.b.y); i<round(tr.c.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
				left = left + k_bc;
				right = right + k_ac;
			}
			break;
	}   // switch(shadestyle){
	*/
}

void Grapher::draw_triangle(Triangle3D *triangle) {
}

void Grapher::draw_polygon(Polygon2D *polygon) {
}

void Grapher::draw_polygon(Polygon3D *polygon) {
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
					pixels[y * grapher->width + x] = 255 << 24 + color;
				else
					pixels[y * grapher->width + x] = radius << 24 + color;
			}
		}
	SDL_SetTextureBlendMode(sdltexture, SDL_BLENDMODE_BLEND);	// Enable alpha
	SDL_UpdateTexture(sdltexture, NULL, pixels, grapher->width * sizeof(Uint32));
	return sdltexture;
}
