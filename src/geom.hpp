/*
	SF-Engine

	This file has routines for geometrics.
*/

/*
TODO:
- Class template for 2D and 3D Vertex, Triangle, Polygon, Vector etc.
- Convert from 2D to 3D and vice versa
- Construct objects as meshes instead of Triangle objects to get rid of vertex/vertice duplicates
- For all shapes: area, volume, intersection, distance, normal
- Is point inside a circle
- Is point at line, linesegment, circle's circumference etc.
- Vector addition, dot product etc.
- Create new object after calculating and preserve original coordinates to prevent cumulative rounding errors
- More clarity to classes and structures (Point and Coordinate) - which have only coordinates, which have color, which have shading style etc.
- Curves (is Bezier group enough?)
*/

#ifndef GEOM_HPP
	#define GEOM_HPP


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
	#include "types.hpp"
	#include "color.hpp"

	/*
	class Coordinate2D {
		public:
			float x, y;
	};

	class Coordinate3D {
		public:
			float x, y, z;
	};
	*/

	class Point {
		public:
			float x, y;
			Point();
			Point(float x, float y);
			float distance_from_origo();
			void rotate(float angle);
	};

	class Point3D {
		public:
			float x, y, z;
			Point3D();
			Point3D(float x, float y, float z);
			float distance_from_origo();
			void rotate(float angle_x, float angle_y, float angle_z);
	};

	class Vector2D {
		public:
			//float x, y;	// Location
			float i, j;		// Direction / force
	};

	class Vector3D {
		public:
			//float x, y, z;	// Location
			float i, j, k;		// Direction / force
	};

	class Boundingbox2D {
		// TODO: space diagonal
		public:
			float x_min, x_max, y_min, y_max;
			float width, height;
	};

	class Line {
		public:
			// y = k*x + b;	// k = slope
			//float k;
			//float b;
			//Line();
			Line get_normal();
	};

	class Linesegment2D {
		public:
			Point point_a, point_b;
			Linesegment2D();
			Linesegment2D(Point point_a, Point point_b);
			//float length();
			//Coordinate2D centerpoint();
			float get_slope();
			Line get_normal();
	};

	class Bezier {
	};

	class Coordinategrid {
		public:
			float x_min;
			float x_max;
			float y_min;
			float y_max;
			//int width;
			//int height;
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
			void zoom(float factor);
	};

	/*
	class Vertex2D : public Point {
		public:
			Color color;
	};

	class Vertex3D : public Point3D {
		public:
			Color color;
	};
	*/

	/*
	struct point2d {
		float x;
		float y;
	};

	struct point3d {
		float x;
		float y;
		float z;
	};
	*/

	class Triangle {
		public:
			float location_x = 0;
			float location_y = 0;
			unsigned char shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
			Uint32 color = 0;
			std::vector<Point*> vertexes;
			Triangle();
			~Triangle();
			void set_vertexes(Point* vertex1, Point* vertex2, Point* vertex3);
			void rotate(float angle);
	};

	class Polygon {
		// Triangle group
		public:
			std::vector<Triangle*> triangles;
			//std::vector<Vertex2D> vertexes;
				//std::vector<Vertex2D> vertex2darray, vertex2darray_stored;
				//std::vector<Vertex3D> vertex3darray, vertex3darray_stored;
				//std::vector<unsigned int> face2darray, face2darray_stored;
				//std::vector<unsigned int> face3darray, face3darray_stored;
			void add_triangle(Triangle* triangle);
			//unsigned int color;
			unsigned char shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
			Polygon();
			~Polygon();
			void set_color(Uint32 color);
			void set_location(Point location);
			void move(Vector3D* direction);
			void scale(float multiplier);
			//void scale(float scale_x, float scale_y, float scale_z);
			void rotate(float angle);
			Boundingbox2D get_boundingbox();
	};

	/*
		class Object2D {
		};
		class Object3D {
		};
	*/

	class Square2D {
		Point get_centerpoint();
		float get_width();
		float get_height();
		float get_x_min();
		float get_x_max();
		float get_y_min();
		float get_y_max();
	};

	float get_distance(Point* point_a, Point* point_b);
	//float get_distance(Point3D point_a, Point3D point_b);

	bool overlap(Polygon* polygon1, Polygon* polygon2);

#endif // GEOM_HPP
