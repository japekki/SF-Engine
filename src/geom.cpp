/*
	SF-Engine

	This file has routines for geometrics.
*/

#include <math.h>
#include "geom.hpp"
#include "math.hpp"

int Coordinategrid::get_x_min() {
	return x_min;
}

int Coordinategrid::get_x_max() {
	return x_max;
}

int Coordinategrid::get_y_min() {
	return y_min;
}

int Coordinategrid::get_y_max() {
	return y_max;
}

void Coordinategrid::set_x_min(int new_x_min) {
	x_min = new_x_min;
	width = abs(x_max - x_min);
}

void Coordinategrid::set_x_max(int new_x_max) {
	x_max = new_x_max;
	width = abs(x_max - x_min);
}

void Coordinategrid::set_y_min(int new_y_min) {
	y_min = new_y_min;
	height = abs(y_max - y_min);
}

void Coordinategrid::set_y_max(int new_y_max) {
	y_max = new_y_max;
	height = abs(y_max - y_min);
}

Coordinategrid::Coordinategrid() {
}

Coordinategrid::Coordinategrid(int x_min, int x_max, int y_min, int y_max) {
	// x increases from left to right, y increases from top to bottom
	// TODO: horizontal and vertical reverse / mirroring (?)
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->width = x_max - x_min;
	this->height = y_max - y_min;
}

Point2D::Point2D() {
}

Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point2D::rotate(float angle) {
	float new_x, new_y;
	// Z axis:
	new_x = x * cos(angle) - y * sin(angle);
	new_y = x * sin(angle) + y * cos(angle);
	x = new_x;
	y = new_y;
}

Point3D::Point3D() {
}

Point3D::Point3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point3D::rotate(float angle_x, float angle_y, float angle_z) {
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

Triangle2D::Triangle2D() {
}

Triangle2D::~Triangle2D() {
	//delete this->vertexes;	// FIXME: segfault
	//delete[] this->vertexes;	// FIXME: segfault
}

void Triangle2D::set_vertexes(Vertex2D *vertex1, Vertex2D *vertex2, Vertex2D *vertex3) {
	this->vertexes[0] = vertex1;
	this->vertexes[1] = vertex2;
	this->vertexes[2] = vertex3;
}

void Triangle2D::rotate(float angle) {
	this->vertexes[0]->rotate(angle);
	this->vertexes[1]->rotate(angle);
	this->vertexes[2]->rotate(angle);
}

void Polygon2D::add_triangle(Triangle2D *triangle) {
	this->triangles.push_back(triangle);
}

Triangle3D::Triangle3D() {
}

Triangle3D::~Triangle3D() {
	//delete this->vertexes;	// FIXME: segfault
	//delete[] this->vertexes;	// FIXME: segfault
}

void Triangle3D::rotate(float angle_x, float angle_y, float angle_z) {
}
