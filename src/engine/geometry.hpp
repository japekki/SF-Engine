/*
	SF-Engine

	This file has routines for geometrics.
*/

/*
TODO:
- Class template for 2D and 3D Vertex, Triangle, Polygon, Vector etc.
- Convert between 2D and 3D
- Construct objects as meshes instead of Triangle objects to get rid of vertex/vertice duplicates
- For all shapes: area, volume, intersection, distance, normal
- Is point inside a circle
- Is point at line, linesegment, circle's circumference etc.
- Create new object after calculating and preserve original coordinates to prevent cumulative rounding errors
- More clarity to classes and structures (Point and Coordinate) - which have only coordinates, which have color, which have shading style etc.
- Curves
*/

#ifndef GEOMETRY_HPP
	#define GEOMETRY_HPP

	// CONSTANTS:
		#define PI 3.14159265358979323846246
		#define PIX2 2*PI
		#define PIPER2 PI/2
		// MATH.H:
		// M_El			2.7182818284590452353602874713526625L	// e
		// M_LOG2El		1.4426950408889634073599246810018921L	// log_2 e
		// M_LOG10El	0.4342944819032518276511289189166051L	// log_10 e
		// M_LN2l		0.6931471805599453094172321214581766L	// log_e 2
		// M_LN10l		2.3025850929940456840179914546843642L	// log_e 10
		// M_PIl		3.1415926535897932384626433832795029L	// pi
		// M_PI_2l		1.5707963267948966192313216916397514L	// pi/2
		// M_PI_4l		0.7853981633974483096156608458198757L	// pi/4
		// M_1_PIl		0.3183098861837906715377675267450287L	// 1/pi
		// M_2_PIl		0.6366197723675813430755350534900574L	// 2/pi
		// M_2_SQRTPIl	1.1283791670955125738961589031215452L	// 2/sqrt(pi)
		// M_SQRT2l		1.4142135623730950488016887242096981L	// sqrt(2)
		// M_SQRT1_2l	0.7071067811865475244008443621048490L	// 1/sqrt(2)

	// UNIT CIRCLE:
		// x = cos(angle)
		// y = sin(angle)

	// X axis is vertical on screen: "width"
	// Y axis is horizontal on screen: "height"
	// Z axis is trough the monitor: "depth"

	// CONSTANTS:
		#define POLYGON_SHADESTYLE_NODRAW 0
		#define POLYGON_SHADESTYLE_POINT 1
		#define POLYGON_SHADESTYLE_WIREFRAME 2
		#define POLYGON_SHADESTYLE_SINGLE 3
		#define POLYGON_SHADESTYLE_FLAT 4
		#define POLYGON_SHADESTYLE_GOURAUD 5
		#define POLYGON_SHADESTYLE_TEXTURE 6

	#include <SDL.h>
	#include <vector>
	#include "color.hpp"

	class Vector {
		public:
			float i = 0;
			float j = 0;
			Vector();
			Vector(float i, float j);
			void rotate(float angle);
			void add(Vector vector);
			void add(float i, float j);
			void sub(Vector vector);
			void sub(float i, float j);
			void multiply(float multiplier);
			float dotproduct(Vector vector);
	};

	class Point {
		public:
			float x = 0;
			float y = 0;
			Point();
			Point(float x, float y);
			float distance_from_origo();
			void move(Vector heading);
			void move(float x, float y);
			void rotate(float angle);
			float angle(Point point);
	};

	class Boundingbox {
		// TODO: space diagonal
		public:
			float x_min = 0;
			float x_max = 0;
			float y_min = 0;
			float y_max = 0;
			float width = 0;
			float height = 0;
	};

	class Line {
		public:
			// y = k*x + b;	// k = slope
			//float k;
			//float b;
			//Line();
			Line get_normal();
	};

	class Linesegment {
		public:
			Point point_a, point_b;
			Linesegment();
			Linesegment(Point point_a, Point point_b);
			float get_length();
			Point get_center();
			float get_slope();
			Line get_normal();
	};

	class Path {
		public:
			std::vector<Point> points;
			void append(Point point);
			void close();
			uint32_t get_length();
	};

	class Bezier {
	};

	class Coordinategrid {
		private:
			float width = 0;
			float height = 0;
		public:
			float zooming = 1;
			float x_min = 0;
			float x_max = 0;
			float y_min = 0;
			float y_max = 0;

			uint32_t width_in_pixels = 0;		// Amount of pixels in grid's width
			uint32_t height_in_pixels = 0;	// Amount of pixels in grid's height
			Point center;	//(0, 0);
			void set_center(Point location);
			void set_center(float x, float y);
			Coordinategrid();
			Coordinategrid(int width_in_pixels, int height_in_pixels, float x_min, float x_max, float y_min, float y_max);
			void set(int width_in_pixels, int height_in_pixels, float x_min, float x_max, float y_min, float y_max);
			float transform_width(float width);
			float transform_height(float height);
			Point transform(Point coordinate);
			// TODO: Better names:
				float transform_width_backwards(float width);
				float transform_height_backwards(float height);
				Point transform_backwards(Point coordinate);
			Linesegment transform(Linesegment linesegment);
			void set_zoom(float zooming);
			void zoom(float zooming);
			void zoom_reset();
			float get_width();
			float get_height();
	};

	class Triangle {
		public:
			unsigned char shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
			uint32_t color = 0;
			std::vector<Point> vertexes;	// max 3
			Triangle();
			~Triangle();
			void set_vertexes(Point vertex1, Point vertex2, Point vertex3);
			void move_vertexes(Vector heading);
			void rotate_vertexes(float angle);
	};

	class Trianglelist {	// class Polygon already exists in OpenGL/SDL @ Windows
		// Triangle group
		public:
			std::vector<Triangle*> triangles;
			// TODO:
				//std::vector<Vertex> vertexes;
				//std::vector<Vertex> vertex2darray, vertex2darray_stored;
				//std::vector<uint32_t> face2darray, face2darray_stored;
			void add_triangle(Triangle* triangle);
			//uint32_t color;
			unsigned char shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
			Trianglelist();
			~Trianglelist();
			void set_color(uint32_t color);
			void set_location(Point location);
			//void move(Vector direction);
			void move_triangles(Vector heading);
			void scale_triangles(float multiplier);
			//void rotate(float angle);
			//void scale(float scale_x, float scale_y, float scale_z);
			void rotate_triangles(float angle);
			Boundingbox get_boundingbox();
	};

	class Square {
		Point get_centerpoint();
		float get_width();
		float get_height();
		float get_x_min();
		float get_x_max();
		float get_y_min();
		float get_y_max();
	};

	float get_distance(Point point_a, Point point_b);
	float get_angle(Point point1, Point point2);

	float ball_get_area(float radius);
	float ball_get_volume(float radius);

	//bool overlap(Polygon* polygon1, Polygon* polygon2);

	namespace geom {
		float angle(Point point_a, Point point_b);
	}

#endif // GEOMETRY_HPP
