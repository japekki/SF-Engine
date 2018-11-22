/*
	SF-Engine

	This file has mathematical routines.
*/

#include "math.hpp"

/*
//#include "options.hpp"

#include <math>

// TODO:
// Functions that return
// - Intersections of circles
// - Intersections of circle and line
// - Is point inside a circle
// - Is point at line or linesegment
// - Vector addition, dot product etc.


//Class Vec3 {
//	float x,y,z;    // Location
//	float i,j,k;    // Direction
//}


// In unit circle:
// cos(a) = x
// sin(a) = y

*/
Point::Point() {
}

Point::Point(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

void Point::draw() {
}

/*
void Point::rotate(float angle_x, float angle_y, float angle_z) {
	float new_x, new_y, new_z;
	// Z axis:
	new_x = x * cos(angle_z) - y * sin(angle_z);
	new_y = x * sin(angle_z) + y * cos(angle_z);
	x = new_x;
	y = new_y;
	// X axis:
	new_y = y * cos(angle_x) - z * sin(angle_x);
	new_z = y * sin(angle_x) + z * cos(angle_x);
	y = new_y;
	z = new_z;
	// Y axis:
	new_z = z * cos(angle_y) - x * sin(angle_y);
	new_x = z * sin(angle_y) + x * cos(angle_y);
	y = new_y;
	x = new_x;
}

float Point::distance_from_origo() {
	return sqrt(x*x + y*y + z*z);
};

float Point::distance_from_point(Point point) {
	return sqrt(pow((x-point.x),2) + pow((y-point.y),2) + pow((z-point.z),2));
}

Line::Line() {
}

Line Line::getnormal() {
}

bool Line::intersects(Point point) {
}

bool Line::intersects(Line Line) {
}

bool Line::intersects(Linesegment Linesegment) {
}

bool Line::intersects(Ball Ball) {
}


Linesegment::Linesegment() {
}

//bool Linesegment::intersects(Point point) {
}

float circle_area(float radius) {
	// Circle's area
	// A = pi * r^2
	return PI*radius*radius;
}

float ball_area(float radius) {
	// Ball's area
	// A = 4 * pi * r^2
	return 4 * PI * radius*radius;
}

float ball_volume(float radius) {
	// Pallon tilavuus
	// V = (4 * pi * r^3) / 3
	return (4 * PI * radius*radius*radius) / 3;
}

float slope(point2d a, point2d b) {
	// How much Y changes, when X changes by one
	// K = delta_y / delta_x
	return (b.y - a.y) / (b.x - a.x);   // ignores Z coordinates
}

float distance(point2d a, point2d b) {
	// distance = sqrt(delta_x^2 + delta_y^2)
	int delta_x = (b.x-a.x);
	int delta_y = (b.y-a.y);
	return sqrt( delta_x*delta_x + delta_y*delta_y );
}

float distance(point3d a, point3d b) {
	// distance = sqrt(delta_x^2 + delta_y^2 + delta_z^2)
	int delta_x = (b.x-a.x);
	int delta_y = (b.y-a.y);
	int delta_z = (b.z-a.z);
	return sqrt( delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
}
*/
