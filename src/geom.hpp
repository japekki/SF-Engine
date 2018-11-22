#ifndef GEOM_HPP
	#define GEOM_HPP

	// TODO:
	// - converter from Vertex2D into Vertex3D
	// - converter from Vertex3D into Vertex2D
	// - converter from Triangle2D into Triangle3D
	// - converter from Triangle3D into Triangle2D

	#include <SDL.h>
	#include <vector>
	#include "types.hpp"
	//#include "grapher.hpp"
	#include "color.hpp"

	// CONSTANTS:
		#define POLYGON_SHADESTYLE_NODRAW 0
		#define POLYGON_SHADESTYLE_POINT 1
		#define POLYGON_SHADESTYLE_WIREFRAME 2
		#define POLYGON_SHADESTYLE_SINGLE 3
		#define POLYGON_SHADESTYLE_FLAT 4
		#define POLYGON_SHADESTYLE_GOURAUD 5
		#define POLYGON_SHADESTYLE_TEXTURE 6

	// X axis is vertical on screen
	// Y axis is horizontal on screen
	// Z axis is "trough the monitor"

	struct Coordinate2D {
		float x, y;
	};

	struct Coordinate3D {
		float x, y, z;
	};

	class Coordinategrid {
		public:
			int x_min;
			int x_max;
			int y_min;
			int y_max;
			int width;
			int height;
			bool centered = true;
			bool with_perspective = true;
			Coordinategrid();
			Coordinategrid(int x_min, int x_max, int y_min, int y_max);
			int get_x_min();
			int get_x_max();
			int get_y_min();
			int get_y_max();
			void set_x_min(int new_x_min);
			void set_x_max(int new_x_max);
			void set_y_min(int new_y_min);
			void set_y_max(int new_y_max);
	};

	class Vertex2D {
		float x, y;
		Color color;
	};

	class Triangle2D {
		float location_x = 0;
		float location_y = 0;
		float rotation_angle = 0;	// Z axis
		unsigned char shadestyle = POLYGON_SHADESTYLE_NODRAW;
		Vertex2D *vertexes[3];
		void set_vertexes(Vertex2D *vertex1, Vertex2D *vertex2, Vertex2D *vertex3);
	};

	class Polygon2D {
		std::vector<Triangle2D*> triangles;
		void add_triangle(Triangle2D *triangle);
	};

	class Vertex3D {
		float x, y, z;
		Color color;
	};

	class Triangle3D {
		float location_x = 0;
		float location_y = 0;
		float rotation_angle = 0;	// Z axis
		Vertex3D *vertexes[3];
		void set_vertexes(Vertex3D *vertex1, Vertex3D *vertex2, Vertex3D *vertex3);
	};

	class Polygon3D {
		std::vector<Triangle3D*> triangles;
		void add_triangle(Triangle3D *triangle);
	};

	class Vector2D {
		float i, j;
	};

	class Vector3D {
		float i, j, k;
	};

	/*
	TODO

	class Bezier {}
	class Voxel {}
	*/

#endif // GEOM_HPP
