#ifndef GEOM_HPP
	#define GEOM_HPP

	// TODO:
	// - Converter from Vertex2D into Vertex3D
	// - Converter from Vertex3D into Vertex2D
	// - Converter from Triangle2D into Triangle3D
	// - Converter from Triangle3D into Triangle2D
	// - class Bezier {}
	// - class Voxel {}
	// - Intersections of circles
	// - Intersections of circle and line
	// - Is point inside a circle
	// - Is point at line or linesegment
	// - Vector addition, dot product etc.
	// - Create new object after calculating and preserve original coordinates to prevent cumulative rounding errors

	// CONSTANTS:
		#define PI 3.14159265358979323846246
		#define PIX2 2*PI
		#define PIPER2 PI/2
		// MATH.H:
		// M_El			2.7182818284590452353602874713526625L	// e
		// M_LOG2El		1.4426950408889634073599246810018921L	// log_2 e
		// M_LOG10El	0.4342944819032518276511289189166051L	// log_10 e
		// M_LN2l		0.6931471805599453094172321214581766L	// log_e 2
		// M_LN10l	    2.3025850929940456840179914546843642L	// log_e 10
		// M_PIl		3.1415926535897932384626433832795029L	// pi
		// M_PI_2l	    1.5707963267948966192313216916397514L	// pi/2
		// M_PI_4l	    0.7853981633974483096156608458198757L	// pi/4
		// M_1_PIl	    0.3183098861837906715377675267450287L	// 1/pi
		// M_2_PIl	    0.6366197723675813430755350534900574L	// 2/pi
		// M_2_SQRTPIl	1.1283791670955125738961589031215452L	// 2/sqrt(pi)
		// M_SQRT2l		1.4142135623730950488016887242096981L	// sqrt(2)
		// M_SQRT1_2l	0.7071067811865475244008443621048490L	// 1/sqrt(2)

	// UNIT CIRCLE:
		// x = cos(angle)
		// y = sin(angle)

	#include <SDL.h>
	#include <vector>
	#include "types.hpp"
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

	class Point2D {
		public:
			float x, y;
			Point2D();
			Point2D(float x, float y);
			void rotate(float angle);
			//float distance_from_origo();
			//float distance_from_point(Point2D point2d);
	};

	class Point3D {
		public:
			float x, y, z;
			Point3D();
			Point3D(float x, float y, float z);
			void rotate(float angle_x, float angle_y, float angle_z);
			//float distance_from_origo();
			//float distance_from_point(Point3D point3d);
	};

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

	class Vertex2D : public Point2D {
		public:
			Color color;
	};

	class Triangle2D {
		public:
			float location_x = 0;
			float location_y = 0;
			unsigned char shadestyle = POLYGON_SHADESTYLE_NODRAW;
			Vertex2D *vertexes[3];
			Triangle2D();
			~Triangle2D();
			void set_vertexes(Vertex2D *vertex1, Vertex2D *vertex2, Vertex2D *vertex3);
			void rotate(float angle);
	};

	class Polygon2D {
		std::vector<Triangle2D*> triangles;
		void add_triangle(Triangle2D *triangle);
	};

	class Vertex3D : public Point3D {
		Color color;
	};

	class Triangle3D {
		float location_x = 0;
		float location_y = 0;
		Vertex3D *vertexes[3];
		Triangle3D();
		~Triangle3D();
		void set_vertexes(Vertex3D *vertex1, Vertex3D *vertex2, Vertex3D *vertex3);
		void rotate(float angle_x, float angle_y, float angle_z);
	};

	class Polygon3D {
		std::vector<Triangle3D*> triangles;
		void add_triangle(Triangle3D *triangle);
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

	struct point2d {
		float x;
		float y;
	};

	struct point3d {
		float x;
		float y;
		float z;
	};

	struct square2d {
		float x1, y1, x2, y2;
	};

	struct circle2d {
		float x, y, r;
	};

#endif // GEOM_HPP
