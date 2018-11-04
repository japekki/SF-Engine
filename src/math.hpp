#ifndef MATH_HPP
#define MATH_HPP

// CONSTANTS:
	#define PI 3.14159265358979323846246
	#define PIX2 2*PI
	#define PIPER2 PI/2
	/*  MATH.H:
	M_El		2.7182818284590452353602874713526625L  // e
	M_LOG2El	1.4426950408889634073599246810018921L  // log_2 e
	M_LOG10El	0.4342944819032518276511289189166051L  // log_10 e
	M_LN2l		0.6931471805599453094172321214581766L  // log_e 2
	M_LN10l	    2.3025850929940456840179914546843642L  // log_e 10
	M_PIl		3.1415926535897932384626433832795029L  // pi
	M_PI_2l	    1.5707963267948966192313216916397514L  // pi/2
	M_PI_4l	    0.7853981633974483096156608458198757L  // pi/4
	M_1_PIl	    0.3183098861837906715377675267450287L  // 1/pi
	M_2_PIl	    0.6366197723675813430755350534900574L  // 2/pi
	M_2_SQRTPIl	1.1283791670955125738961589031215452L  // 2/sqrt(pi)
	M_SQRT2l	1.4142135623730950488016887242096981L  // sqrt(2)
	M_SQRT1_2l	0.7071067811865475244008443621048490L  // 1/sqrt(2)
	*/

//#include <math.h>

//#ifdef WITH_OPENGL
//    #include <GL/gl.h>
//#endif


// TODO: FIXED POINT MATH
// TODO: Should these be used even with OpenGL?
/*
class Fxp {
	// TODO: case->Case
	public:
	Fxp(float param) {
		value = (long)(param * 65536);
	}

	Fxp(long param) {
		value = param;
	}

	Fxp operator + (Fxp param) {
		return Fxp(value + param.value);
	}

	Fxp operator - (Fxp param) {
		return Fxp(value - param.value);
	}

	Fxp operator * (Fxp param) {
		return Fxp((value * param.value));
	}

	Fxp operator / (Fxp param) {
		return Fxp((value << 16) / param.value);
	}

	short GetUint16() {
		return (unsigned short)(value >> 16);
	}

	float GetFloat() {
		return (((float)value) / 65536);
	}

	short Frac() {
		return (unsigned short) value;
	}

	short Round() {
		// TODO: Toimiiko negatiivisilla?
		if ( short(value) < 0 ) {
			// if left fractional bit 1
			return short(value >> 16) + 1;
		}
		else {
			return short(value >> 16);
		}
	}
	// private:
	long value;
	// short most, less
};
*/
/* USAGE:
	fxp value1 = 2.4f;
	fxp value2 = 2.4f;
	fxp value3 = value1 * value2;
	float value4 = value3.GetFloatingPoint();
*/


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

class Point {
	public:
		float x, y, z, a;
		//Uint8 dimensions;   // ignore stuff in higher dimensions when calculating
		Point();
		Point(float x_, float y_, float z_);
		void draw ();
		void rotate(float angle_x, float angle_y, float angle_z);
		float etaisyys_origosta();
		float etaisyys_pisteesta(Point piste);
};

// Hmmm, kumpi oli ensin, muna vai kana?
//class Jana{};
//class Suora{};
//class Ball{};
//jne.

class Suora {
	public:
		// y = kx + b   | k = kulmakerroin
		float K;
		float B;
		//Point leikkauspisteet[];
		Suora();

		Suora normaali();
		//float min_etaisyys_pisteesta();
		//bool leikkaa(Point Piste);
		//bool leikkaa(Suora Suora);
		//bool leikkaa(Jana Jana);
		//bool leikkaa(Ball Ball);
};

class Jana {
	public:
		Point A;
		Point B;
		//Point leikkauspiste;
		Jana();
		//float pituus();
		//float keskipiste();
		//Suora normaali();
		//bool leikkaa(Point Piste);
};

class Viiva {
	public:
		Point kulmat[0];
};

class Ball {
	public:
		//Uint8 dimensions;   // Circle if 2
		//Point leikkauspisteet[];
		Point keskipiste;
		float radius;
		Ball();
		//Point leikkauspiste(Point Piste);
		//Point leikkauspisteet(Suora Suora);
		//Point leikkauspisteet(Jana Jana);
		//Point leikkauspisteet(Ball Circle);
		//Uint8 include(Point Piste);  // Palauttaa: 0 jos keskipisteessa, 1 jos sisalla, 2 jos kehalla. 3 jos ulkona
};

float circle_area(float radius);
float ball_area(float radius);
float ball_volume(float radius);

float kulmakerroin(Point a, Point b);
float distance(Point a, Point b);
float distance(Point a, Point b);

#endif // MATH_HPP
