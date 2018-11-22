/*
	SF-Engine

	This file has routines for geometrics.
*/

#include <math.h>
#include "geom.hpp"
#include "misc.hpp"
#include "math.hpp"
#include "options.hpp"

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

void Triangle2D::set_vertexes(Vertex2D *vertex1, Vertex2D *vertex2, Vertex2D *vertex3) {
	this->vertexes[0] = vertex1;
	this->vertexes[1] = vertex2;
	this->vertexes[2] = vertex3;
}

void Polygon2D::add_triangle(Triangle2D *triangle) {
	this->triangles.push_back(triangle);
}

