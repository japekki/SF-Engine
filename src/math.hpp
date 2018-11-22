#ifndef MATH_HPP
	#define MATH_HPP

/*
	// CONSTANTS:
		#define PI 3.14159265358979323846246
		#define PIX2 2*PI
		#define PIPER2 PI/2
		//  MATH.H:
		//M_El		2.7182818284590452353602874713526625L  // e
		//M_LOG2El	1.4426950408889634073599246810018921L  // log_2 e
		//M_LOG10El	0.4342944819032518276511289189166051L  // log_10 e
		//M_LN2l		0.6931471805599453094172321214581766L  // log_e 2
		//M_LN10l	    2.3025850929940456840179914546843642L  // log_e 10
		//M_PIl		3.1415926535897932384626433832795029L  // pi
		//M_PI_2l	    1.5707963267948966192313216916397514L  // pi/2
		//M_PI_4l	    0.7853981633974483096156608458198757L  // pi/4
		//M_1_PIl	    0.3183098861837906715377675267450287L  // 1/pi
		//M_2_PIl	    0.6366197723675813430755350534900574L  // 2/pi
		//M_2_SQRTPIl	1.1283791670955125738961589031215452L  // 2/sqrt(pi)
		//M_SQRT2l	1.4142135623730950488016887242096981L  // sqrt(2)
		//M_SQRT1_2l	0.7071067811865475244008443621048490L  // 1/sqrt(2)

	//#include <math>

	class Coordplane {
		int min_x, min_y, max_x, max_y;
		// int width, height; // res_x and res_y for now
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

	struct vec2 {
		// Sijainti:
		float x;
		float y;
		// Suunta:
		float i;
		float j;
	};

	struct vec3 {
		float x;
		float y;
		float z;
	};

	struct vektori {
		float x;
		float y;
		float z;
		float i;
		float j;
		float k;
	};

	struct square2d {
		float x1, y1, x2, y2;
	};

	struct circle2d {
		float x, y, r;
	};
*/

	class Point {
		public:
			float x, y, z, a;
			//unsigned char dimensions;   // ignore stuff in higher dimensions when calculating
			Point();
			Point(float x_, float y_, float z_);
			void draw ();
			void rotate(float angle_x, float angle_y, float angle_z);
			float distance_from_origosta();
			float distance_from_point(Point point);
	};

/*
	//class Linesegment{};
	//class Line{};
	//class Ball{};

	class Line {
		public:
			// y = kx + b   | k = slope
			float K;
			float B;
			//Point intersections[];
			Line();

			Line normal();
			//float min_distance_from_point();
			//bool intersects(Point point);
			//bool intersects(Line line);
			//bool intersects(Linesegment linesegment);
			//bool intersects(Ball ball);
	};

	class Linesegment {
		public:
			Point A;
			Point B;
			//Point intersection;
			Linesegment();
			//float length();
			//float centerpoint();
			//Line normal();
			//bool intersects(Point point);
	};

	class Line {
		public:
			Point corners[0];
	};

	class Ball {
		public:
			//unsigned char dimensions;   // Circle if 2
			//Point intersections[];
			Point centerpoint;
			float radius;
			Ball();
			//Point intersects(Point point);
			//Point intersects(Line line);
			//Point intersects(Linesegment linesegment);
			//Point intersects(Ball Circle);
			//unsigned char includes(Point point);  // Return: 0 if center point, 1 if inside, 2 if at circumference. 3 if outside
	};

	float circle_area(float radius);
	float ball_area(float radius);
	float ball_volume(float radius);

	float slope(Point a, Point b);
	float distance(Point a, Point b);
	float distance(Point a, Point b);

*/

#endif // MATH_HPP
