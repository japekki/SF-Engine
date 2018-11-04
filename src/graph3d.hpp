#ifndef GRAPH3D_HPP
	#define GRAPH3D_HPP

	#include <vector>
	//#include "options.hpp"
	#include <SDL/SDL.h>
	#include "graph.hpp"

struct pixel3d {
	float r, g, b;
	Uint32 color;
};

class Pixel3d {
	public:
		float r, g, b;
		Uint32 color;
		float x, y, z, a;
		Pixel3d();
		void setcolor(Uint32 color);
		void setcolor(float r, float g, float b);
		Uint32 getcolor(SDL_Surface *sdlsurface);
		//float getcolor();
};

struct vertex3d_struct {
	float x, y, z;
	float r, g, b;
	Uint32 color;
};

/*    #ifdef WITH_OPENGL
		class Vertex3d {
		public:
			GLfloat x,y,z;
			GLfloat r,g,b;
			Vertex3d();
		};
*/
		class Vertex3d {
		public:
			float x,y,z;
			float r,g,b;
			Vertex3d();
			Uint32 colorint(SDL_Surface *sdlsurface);
		};


//    struct triangle3d {
//        Pixel3d a, b, c;
//        Uint32 color;
//    };

	struct boundingbox  {
	// TODO: Class, avaruuslävistäjä, ...
		float x_min, x_max, y_min, y_max, z_min, z_max;
		float size_x, size_y, size_z;
	};

	class Zbuf {
		public:
		std::vector<float> z;
		Zbuf();
		Zbuf(Uint16 size_x, Uint16 size_y);
		void resize(Uint32 newsize);
		void reset();
	};

	class Triangle3d {
		public:
			Pixel3d a, b, c;
			Uint8 shadestyle;
			Uint32 color;
			Triangle3d();
			~Triangle3d();
			//void draw();
			void draw(SDL_Surface *sdlsurface);
	};

	struct triangle3d {
		pixel3d a, b, c;
		Uint8 shadestyle;
		Uint32 color;
	};

	void draw3d_pixel(int x, int y, float z, Uint32 color, SDL_Surface *sdlsurface);
	void draw3d_vline(Point a, Point b, Uint32 color, SDL_Surface *sdlsurface);
	void draw3d_hline(Pixel3d a, Pixel3d b, Uint32 color, SDL_Surface *sdlsurface);
	void draw3d_hlinesmooth(Pixel3d a, Pixel3d b, SDL_Surface *sdlsurface);
	void draw3d_line(Point a, Point b, Uint32 color, SDL_Surface *sdlsurface);
	//void draw3d_triangle(triangle3d tr, Uint8 shadestyle, SDL_Surface *sdlsurface);
	void generate_cube(float x, float y, float z, float scale, float r, float g, float b);

#endif // GRAPH3D_HPP
