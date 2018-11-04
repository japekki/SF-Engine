//#include "vakiot.hpp"
//#include "options.hpp"
#include "math.hpp"
#include <math.h>

// TODO:
// Funktio, joka palauttaa:
// - Ympyröiden leikkauspisteet
// - Ympyrän ja suoran leikkauspisteet
// - Onko piste ympyrän sisällä
// - Onko piste suoralla/janalla
// - Vektorien yhteenlasku, pistetulo yms.

/*
Class Vec3 {
	float x,y,z;    // Location
	float i,j,k;    // Direction
}
*/

// Yksikköympyrässä:
// cos(a) = x
// sin(a) = y

Point::Point() {
}

Point::Point(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

void Point::draw() {
}

void Point::rotate(float angle_x, float angle_y, float angle_z) {
	float new_x, new_y, new_z;
	// Z-akselin suhteen:
	new_x = x * cos(angle_z) - y * sin(angle_z);
	new_y = x * sin(angle_z) + y * cos(angle_z);
	x = new_x;
	y = new_y;
	// X-akselin suhteen:
	new_y = y * cos(angle_x) - z * sin(angle_x);
	new_z = y * sin(angle_x) + z * cos(angle_x);
	y = new_y;
	z = new_z;
	// Y-akselin suhteen:
	new_z = z * cos(angle_y) - x * sin(angle_y);
	new_x = z * sin(angle_y) + x * cos(angle_y);
	y = new_y;
	x = new_x;
}

float Point::etaisyys_origosta() {
	return sqrt(x*x + y*y + z*z);
};

float Point::etaisyys_pisteesta(Point Piste) {
	return sqrt(pow((x-Piste.x),2) + pow((y-Piste.y),2) + pow((z-Piste.z),2));
}

Suora::Suora() {
}

Suora Suora::normaali() {
	//Suora Normaali;
	//Normaali = Suora;
	//Normaali.
}
/*
bool Suora::leikkaa(Point Piste) {
}

bool Suora::leikkaa(Suora Suora) {
}

bool Suora::leikkaa(Jana Jana) {
}

bool Suora::leikkaa(Ball Ball) {
}
*/

Jana::Jana() {
}
/*
bool Jana::leikkaa(Point Piste) {
}
*/
float circle_area(float radius) {
	// Ympyrän pinta-ala
	// A = pi * r^2
	return PI*radius*radius;
}

float ball_area(float radius) {
	// Pallon pinta-ala
	// A = 4 * pi * r^2
	return 4 * PI * radius*radius;
}

float ball_volume(float radius) {
	// Pallon tilavuus
	// V = (4 * pi * r^3) / 3
	return (4 * PI * radius*radius*radius) / 3;
}

float kulmakerroin(point2d a, point2d b) {
	// Kuinka paljon Y muuttuu, kun X muuttuu yhdellä
	// K = delta_y / delta_x
	return (b.y - a.y) / (b.x - a.x);   // Ei huomioi Z-koordinaatteja
}

float distance(point2d a, point2d b) {
	// etaisyys = sqrt(delta_x^2 + delta_y^2)
	int delta_x = (b.x-a.x);
	int delta_y = (b.y-a.y);
	return sqrt( delta_x*delta_x + delta_y*delta_y );
}

float distance(point3d a, point3d b) {
	// etaisyys = sqrt(delta_x^2 + delta_y^2 + delta_z^2)
	int delta_x = (b.x-a.x);
	int delta_y = (b.y-a.y);
	int delta_z = (b.z-a.z);
	return sqrt( delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
}
