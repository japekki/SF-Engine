#include <math.h>
#include "geom.hpp"
#include "math.hpp"

float Point::distance_from_origo() {
	return sqrt(x*x + y*y);
};

float Point3D::distance_from_origo() {
	return sqrt(x*x + y*y + z*z);
};

/*
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
	//width = abs(x_max - x_min);
}

void Coordinategrid::set_x_max(int new_x_max) {
	x_max = new_x_max;
	//width = abs(x_max - x_min);
}

void Coordinategrid::set_y_min(int new_y_min) {
	y_min = new_y_min;
	//height = abs(y_max - y_min);
}

void Coordinategrid::set_y_max(int new_y_max) {
	y_max = new_y_max;
	//height = abs(y_max - y_min);
}
*/

void Coordinategrid::zoom(float factor) {
	this->x_min *= factor;
	this->x_max *= factor;
	this->y_min *= factor;
	this->y_max *= factor;
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
	//this->width = x_max - x_min;
	//this->height = y_max - y_min;
}

Point::Point() {
	this->x = 0;
	this->y = 0;
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point::rotate(float angle) {
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

Linesegment2D::Linesegment2D(Point point_a, Point point_b) {
	this->point_a = point_a;
	this->point_b = point_b;
}

float Linesegment2D::get_slope() {
	// How much Y changes, when X changes by one
	// K = delta_y / delta_x
	return (point_b.y - point_a.y) / (point_b.x - point_a.x);	// ignores Z coordinates
}

Line Linesegment2D::get_normal() {
	// TODO
}

Triangle::Triangle() {
}

Triangle::~Triangle() {
	//delete this->vertexes;	// FIXME: segfault
	//delete[] this->vertexes;	// FIXME: segfault
}

void Triangle::set_vertexes(Point* vertex1, Point* vertex2, Point* vertex3) {
	this->vertexes.push_back(vertex1);
	this->vertexes.push_back(vertex2);
	this->vertexes.push_back(vertex3);
}

void Triangle::rotate(float angle) {
	this->vertexes[0]->rotate(angle);
	this->vertexes[1]->rotate(angle);
	this->vertexes[2]->rotate(angle);
}

void Polygon::add_triangle(Triangle* triangle) {
	this->triangles.push_back(triangle);
}

Polygon::Polygon() {
}

Polygon::~Polygon() {
	//delete[] vertexarray;
	for (unsigned int i=0; i<this->triangles.size(); i++)
		delete this->triangles.at(i);
}

void Polygon::set_color(Uint32 color) {
	for (unsigned int i=0; i<this->triangles.size(); i++)
		this->triangles.at(i)->color = color;
}

void Polygon::set_location(Point location) {

}

void Polygon::move(Vector3D* direction) {
}

void Polygon::scale(float multiplier) {
}

void Polygon::rotate(float angle) {
	for (unsigned int i=0; i<this->triangles.size(); i++)
		this->triangles.at(i)->rotate(angle);
}

/*
Boundingbox3D Polygon3D::get_boundingbox() {
	Boundingbox3D result;
	for (int triangle_i = 0; triangle_i < triangles.size(); triangle_i++) {
		Triangle3D tmp_triangle = triangles.at(triangle_i);
		for (int vertex_i = 0; vertex_i < 3; vertex_i++) {
			Point3D tmp_vertex = tmp_triangle.vertexes[vertex_i];
			if (result.x_min > tmp_vertex.x) result.x_min = tmp_vertex.x;
			else if (result.x_max < tmp_vertex.x) result.x_max = tmp_vertex.x;
			if (result.y_min > tmp_vertex.y) result.y_min = tmp_vertex.y;
			else if (result.y_max < tmp_vertex.y) result.y_max = tmp_vertex.y;
			if (result.z_min > tmp_vertex.z) result.z_min = tmp_vertex.z;
			else if (result.z_max < tmp_vertex.z) result.z_max = tmp_vertex.z;
			result.width = fabs(result.x_max - result.x_min);
			result.height = fabs(result.y_max - result.y_min);
			result.depth = fabs(result.z_max - result.z_min);
		}
	}
	return result;
}
*/

/*
float Circle2D::get_area() {
	// Circle's area
	// A = pi * r^2
	return PI*radius*radius;
}

float Ball::get_area() {
	// A = 4 * pi * r^2
	return 4 * PI * radius*radius;
}

float Ball::get_volume() {
	// V = (4 * pi * r^3) / 3
	return (4 * PI * radius*radius*radius) / 3;
}
*/

float get_distance(Point* point_a, Point* point_b) {
	// distance = sqrt(delta_x^2 + delta_y^2)
	float delta_x = (point_b->x - point_a->x);
	float delta_y = (point_b->y - point_a->y);
	return sqrt(delta_x*delta_x + delta_y*delta_y);
}

/*
float get_distance(Point3D point_a, Point3D point_b) {
	// distance = sqrt(delta_x^2 + delta_y^2 + delta_z^2)
	int delta_x = (point_b.x - point_a.x);
	int delta_y = (point_b.y - point_a.y);
	int delta_z = (point_b.z - point_a.z);
	return sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
}
*/

bool overlap(Polygon* polygon1, Polygon* polygon2) {
	return true;	// TODO
}

/*
#ifdef WITH_DEBUGMSG
	// TODO:
	void printvertexarray(std::vector<Vertex3D*> vertexes) {
		for (int i = 0; i < vertexes.size(); i++) {
			Vertex3D tmp = vertexes.at(i);
			printf("x: %f y: %f z: %f r: %f g: %f b: %f\n", tmp.x, tmp.y, tmp.z, tmp.r, tmp.g, tmp.b);
		}
	}
#endif
*/
