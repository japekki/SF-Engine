/*
	SF-Engine

	This file has routines for geometrics.
*/

/*
TODO:
- Converter from Vertex2D into Vertex3D
- Converter from Vertex3D into Vertex2D
- Converter from Triangle2D into Triangle3D
- Converter from Triangle3D into Triangle2D
- Something better than separate 2D and 3D classes/objects (wouldn't want to handle Z coordinates at all if object or world is pure 2D)
- Construct objects as meshes instead of Triangle objects to get rid of vertex/vertice duplicates
- For all shapes: area, volume, intersection, distance, normal
- Is point inside a circle
- Is point at line, linesegment, circle's circumference etc.
- Vector addition, dot product etc.
- Create new object after calculating and preserve original coordinates to prevent cumulative rounding errors
- More clarity to classes and structures (Point and Coordinate) - which have only coordinates, which have color, which have shading style etc.
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

	class Coordinate2D {
		public:
		float x, y;
		float distance_from_origo();
	};

	class Coordinate3D {
		public:
		float x, y, z;
		float distance_from_origo();
	};

	class Point2D : public Coordinate2D {
		public:
			Point2D();
			Point2D(float x, float y);
			void rotate(float angle);
	};

	class Point3D : public Coordinate3D {
		public:
			Point3D();
			Point3D(float x, float y, float z);
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

	class Boundingbox2D  {
		// TODO: space diagonal
		public:
			float x_min, x_max, y_min, y_max;
			float width, height;
	};

	class Boundingbox3D  {
		// TODO: space diagonal
		public:
			float x_min, x_max, y_min, y_max, z_min, z_max;
			float width, height, depth;
	};

	class Line2D {
		public:
			// y = k*x + b   | k = slope
			//float k;
			//float b;
			//Line();
			Line2D get_normal();
	};

	class Line3D {
		public:
			// y = k*x + b   | k = slope
			//float k;
			//float b;
			//Line();
			Line3D get_normal();
	};

	class Linesegment2D {
		public:
			Point2D point_a, point_b;
			Linesegment2D();
			Linesegment2D(Point2D point_a, Point2D point_b);
			//float length();
			//Coordinate2D centerpoint();
			float get_slope();
			Line2D get_normal();
	};

	class Linesegment3D {
		public:
			Point3D point_a, point_b;
			Linesegment3D();
			Linesegment3D(Point3D point_a, Point3D point_b);
			//float length();
			//Coordinate3D centerpoint();
			float get_slope();
			Line3D get_normal();
	};

	class Bezier2D {
	};

	class Bezier3D {
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

	class Vertex3D : public Point3D {
		Color color;
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

	// This parent class "Shape" may solve a chicken and egg problem
	// (for example, Line::intersects(Circle) and Circle::intersects(Line)
	class Shape {
		//unsigned char dimensions;	// 1 - 4
	};

	class Triangle2D {
		public:
			float location_x = 0;
			float location_y = 0;
			unsigned char shadestyle = POLYGON_SHADESTYLE_NODRAW;
			Vertex2D vertexes[3];
			Triangle2D();
			~Triangle2D();
			void set_vertexes(Vertex2D vertex1, Vertex2D vertex2, Vertex2D vertex3);
			void rotate(float angle);
	};

	class Triangle3D {
		public:
			float location_x = 0;
			float location_y = 0;
			unsigned char shadestyle = POLYGON_SHADESTYLE_NODRAW;
			Vertex3D vertexes[3];
			Triangle3D();
			~Triangle3D();
			void set_vertexes(Vertex3D *vertex1, Vertex3D *vertex2, Vertex3D *vertex3);
			void rotate(float angle_x, float angle_y, float angle_z);
	};

	class Polygon2D {
		std::vector<Triangle2D> triangles;
		//std::vector<Vertex2D> vertexes;
			//std::vector<Vertex2D> vertex2darray, vertex2darray_stored;
			//std::vector<Vertex3D> vertex3darray, vertex3darray_stored;
			//std::vector<unsigned int> face2darray, face2darray_stored;
			//std::vector<unsigned int> face3darray, face3darray_stored;
		void add_triangle(Triangle2D &triangle);
		unsigned int color;
		unsigned char shadestyle;
		Polygon2D();
		~Polygon2D();
		//void pushgeom();  // Store original geometry to avoid rounding inaccuracy during serial computation
		//void popgeom();   // Restore original geometry
		//void scale(float scale_x, float scale_y, float scale_z);
		//void scale(float scale);
		Boundingbox2D get_boundingbox();
	};

	class Polygon3D {
		std::vector<Triangle3D> triangles;
		//std::vector<Vertex3D> vertexes;
			//std::vector<Vertex2D> vertex2darray, vertex2darray_stored;
			//std::vector<Vertex3D> vertex3darray, vertex3darray_stored;
			//std::vector<unsigned int> face2darray, face2darray_stored;
			//std::vector<unsigned int> face3darray, face3darray_stored;
		void add_triangle(Triangle3D *triangle);
		unsigned int color;
		unsigned char shadestyle;
		Polygon3D();
		~Polygon3D();
		//void pushgeom();  // Store original geometry to avoid rounding inaccuracy during serial computation
		//void popgeom();   // Restore original geometry
		//void scale(float scale_x, float scale_y, float scale_z);
		//void scale(float scale);
		Boundingbox3D get_boundingbox();
	};

	/*
		class Object2D {
		};
		class Object3D {
		};
	*/

	class Square2D {
		Coordinate2D get_centerpoint();
		float get_width();
		float get_height();
		float get_x_min();
		float get_x_max();
		float get_y_min();
		float get_y_max();
	};

	class Square3D {
		// Cube
		Coordinate3D get_centerpoint();
		float get_width();
		float get_height();
		float get_depth();
		float get_x_min();
		float get_x_max();
		float get_y_min();
		float get_y_max();
		float get_z_min();
		float get_z_max();
	};

	/*
		About dots, circles and balls...
		I have to mention here that I have a distinct opinion about dots/points, circles and balls compared to what is taught by main stream mathematics in schools.
		I consider dot/point to be 1 dimensional object with one parameter: "magnitude".
		A drawn circle is a 2D projection of that dot/point, and ball is 3D projection of that, and hyperball is 4D projection of that.
		By "magnitude" I mean something like: "the amount of power to be or not to be".
		Without reference one cannot say how much that power ("radius") is - just that it is something, and it radiates to infinity.
		Drawing a circumference line around it is just delusive projection upon some particular aspect.
		I consider, what is called "circle area" in schools, to be the volume of that 2D projection.
		I consider, what is called "circle circumference" to be the area of that 2D projection.
		I consider, what is called "ball volume" in schools, to be the area of that 3D projection.
		What is called radius, is really the "magnitude" of a Point, no matter what the degree of projection is.
		So in other words, school mathematics has stumbled on considering these projections to be the "real thing".
		I'm not sure yet whether I should use these heretic terms, or my own interpretations throughout this code.
		I need to think these things trough a bit more... for example is a drawn circle really a 2D projection or is there even more delusions involved: Do circles even exist and what do they really mean?
		So, in other words, I might just make a more abstract primitive objects that have a variable stating the amount of dimensions on which projection level are we working with.
		I'll postpone these circle/ball routines for now since I haven't perfected them yet myself either.

	class Circle2D {
		float x, y, radius;
		float get_area();
		float get_volume();
		//Line2D get_tangent();
	};

	class Circle3D {
		//Line3D get_tangent();
	};

	class Ball {
		float get_area();
		float get_volume();
		//Line3D get_tangent();
	};
	*/

	struct intersection2D {
		bool intersects;
		Coordinate2D intersection;
	};

	struct intersection3D {
		bool intersects;
		Coordinate2D intersection;
	};

	float distance(Coordinate2D point_a, Coordinate2D point_b);
	float distance(Coordinate3D point_a, Coordinate3D point_b);
	intersection2D intersects(Line2D *line_a, Line2D *line_b);
	intersection3D intersects(Line3D *line_a, Line3D *line_b);

	/*
	//void resize3dvertexarray(int n);
	//void resizefacearray(int n);
	//void movecenter();
	//void translatevertexarray();
	//void rotatecenter();
	//void rotatecenter(float angle_x, float angle_y, float angle_z);
	//void rotatevertexarray();
	//void rotatevertexarray(float angle_x, float angle_y, float angle_z);
	*/

	/*
	#ifdef WITH_DEBUGMSG
		void printvertexarray();
	#endif
	*/

#endif // GEOM_HPP
