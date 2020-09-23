#include <math.h>
#include "geometry.hpp"
#include "misc.hpp"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point::move(float x, float y) {
	this->x += x;
	this->y += y;
}

void Point::move(Vector heading) {
	x += heading.i;
	y += heading.j;
}

void Point::rotate(float angle) {
	float new_x, new_y;
	// Z axis:
	new_x = x * cos(angle) - y * sin(angle);
	new_y = x * sin(angle) + y * cos(angle);
	x = new_x;
	y = new_y;
}

float Point::distance_from_origo() {
	return sqrt(x*x + y*y);
};

float Point::angle(Point point) {
	return atan((point.y - this->y) / (point.x - this->x));
}

void Coordinategrid::set_center(Point center) {
	this->center = center;
}

void Coordinategrid::set_center(float x, float y) {
	center.x = x;
	center.x = y;
}

float Coordinategrid::get_width() {
	return x_max - x_min;
}

float Coordinategrid::get_height() {
	return y_max - y_min;
}

float Coordinategrid::transform_width(float width) {
	// Convert grid width into screen/texture width
	// TODO: Not tested
	return zooming * this->width / width_in_pixels * width;
}

float Coordinategrid::transform_height(float height) {
	// Convert grid height into screen/texture height
	// TODO: Not tested
	return zooming * this->height / height_in_pixels * height;
}

float Coordinategrid::transform_width_backwards(float width) {
	// Convert screen/texture width into grid height
	// TODO: Not tested
	//return this->width / width_in_pixels * width / zooming;
	return this->width / width_in_pixels * width * zooming;
}

float Coordinategrid::transform_height_backwards(float height) {
	// Convert screen/texture height into grid height
	// TODO: Not tested
	float screen_aspect = float(width_in_pixels) / height_in_pixels;
	//return this->height / height_in_pixels * height / zooming;
	return this->height / height_in_pixels / screen_aspect * height * zooming;
}

Point Coordinategrid::transform(Point coordinate) {
	// Convert grid coordinate into screen/texture coordinate
	Point result;

	coordinate.x -= center.x;
	coordinate.y -= center.y;

	float screen_aspect = float(width_in_pixels) / height_in_pixels;
	result.x = zooming * float(width_in_pixels) / this->get_width() * coordinate.x + width_in_pixels/2;
	result.y = zooming * float(height_in_pixels) / this->get_height() * screen_aspect * coordinate.y + height_in_pixels/2;

	return result;
}

Point Coordinategrid::transform_backwards(Point coordinate) {
	// Convert screen/texture coordinate into grid coordinate
	Point result;	// = coordinate;

	coordinate.x += center.x;
	coordinate.y += center.y;

	float screen_aspect = float(width_in_pixels) / height_in_pixels;
	result.x = width / width_in_pixels * coordinate.x / zooming - width_in_pixels/2;
	result.y = height / height_in_pixels / screen_aspect * coordinate.y / zooming - height_in_pixels/2;

	return result;
}

Linesegment Coordinategrid::transform(Linesegment linesegment) {
	Linesegment result;
	result.point_a = this->transform(linesegment.point_a);
	result.point_b = this->transform(linesegment.point_b);
	return result;
}

void Coordinategrid::set_zoom(float zooming) {
	this->zooming = zooming;
}

void Coordinategrid::zoom(float zooming) {
	this->zooming *= zooming;
}

void Coordinategrid::zoom_reset() {
	zooming = 1;
}

Coordinategrid::Coordinategrid() {
}

Coordinategrid::Coordinategrid(int width_in_pixels, int height_in_pixels, float x_min, float x_max, float y_min, float y_max) {
	this->set(width_in_pixels, height_in_pixels, x_min, x_max, y_min, y_max);
}

void Coordinategrid::set(int width_in_pixels, int height_in_pixels, float x_min, float x_max, float y_min, float y_max) {
	// x increases from left to right, y increases from top to bottom
	// TODO: horizontal and vertical reverse / mirroring (?)
	this->width_in_pixels = width_in_pixels;
	this->height_in_pixels = height_in_pixels;

	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;

	this->width = abs(x_max - x_min);
	this->height = abs(y_max - y_min);
}

Vector::Vector() {
}

Vector::Vector(float i, float j) {
	this->i = i;
	this->j = j;
}

void Vector::add(Vector vector) {
	this->i += vector.i;
	this->j += vector.j;
}

void Vector::add(float i, float j) {
	this->i += i;
	this->j += j;
}

void Vector::sub(Vector vector) {
	this->i -= vector.i;
	this->j -= vector.j;
}

void Vector::sub(float i, float j) {
	this->i -= i;
	this->j -= j;
}

void Vector::multiply(float multiplier) {
	this->i *= multiplier;
	this->j *= multiplier;
}

float Vector::dotproduct(Vector vector) {
	return this->i * vector.i + this->j * vector.j;
}

void Vector::rotate(float angle) {
	Point point(i, j);
	point.rotate(angle);
	i = point.x;
	j = point.y;
}

Linesegment::Linesegment() {
}

Linesegment::Linesegment(Point point_a, Point point_b) {
	this->point_a = point_a;
	this->point_b = point_b;
}

float Linesegment::get_slope() {
	// How much Y changes, when X changes by one
	// K = delta_y / delta_x
	return (point_b.y - point_a.y) / (point_b.x - point_a.x);	// ignores Z coordinates
}

Line Linesegment::get_normal() {
	Line normal;
	return normal;	// TODO
}

void Path::append(Point point) {
	points.push_back(point);
}

void Path::close() {
	// Connect first and last points with a new linesegment:
	points.push_back(points.front());
}

uint32_t Path::get_length() {
	return points.size();
}

Triangle::Triangle() {
	//log("Triangle::Triangle");
}

Triangle::~Triangle() {
	//delete vertexes;	// FIXME: segfault
	//delete[] vertexes;	// FIXME: segfault
}

void Triangle::set_vertexes(Point vertex1, Point vertex2, Point vertex3) {
	vertexes.push_back(vertex1);
	vertexes.push_back(vertex2);
	vertexes.push_back(vertex3);
}

void Triangle::move_vertexes(Vector heading) {
	for (uint32_t i=0; i<vertexes.size(); i++) {
		vertexes[i].move(heading.i, heading.j);
	}
}

//void Triangle::rotate(float angle) {
	//log("Triangle::rotate");
		//this->rotation_angle = angle;
	//vertexes[0].rotate(angle);
	//vertexes[1].rotate(angle);
	//vertexes[2].rotate(angle);
//}

/*
void Triangle::draw_modified() {
	Triangle triangle;
	triangle.set_vertexes(vertexes[0), vertexes[1), vertexes[2));
	triangle.rotate_vertexes(rotation_angle);
	triangle.move_vertexes(location);
	return triangle;
}
*/

void Trianglelist::add_triangle(Triangle* triangle) {
	triangles.push_back(triangle);
}

Trianglelist::Trianglelist() {
	//log("Trianglelist::Trianglelist");
}

Trianglelist::~Trianglelist() {
	for (uint32_t i=0; i<triangles.size(); i++)
		delete triangles[i];
}

void Trianglelist::set_color(uint32_t color) {
	for (uint32_t i=0; i<triangles.size(); i++)
		triangles[i]->color = color;
}

void Trianglelist::set_location(Point location) {

}

//void Polygon::move_triangles(Vector heading) {
//	for (int i=0; i<triangles.size(); i++)
//		triangles[i)->move(heading);
//}

//void Polygon::scale(float multiplier) {
//}

//void Polygon::rotate(float angle) {
//}

/*
Boundingbox3D Polygon3D::get_boundingbox() {
	Boundingbox3D result;
	for (int triangle_i = 0; triangle_i < triangles.size(); triangle_i++) {
		Triangle3D tmp_triangle = triangles[triangle_i);
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
*/

float ball_get_area(float radius) {
	// A = 4 * pi * r^2
	return 4 * PI * radius*radius;
}

float ball_get_volume(float radius) {
	// V = (4 * pi * r^3) / 3
	return (4 * PI * radius*radius*radius) / 3;
}


float get_distance(Point point_a, Point point_b) {
	// distance = sqrt(delta_x^2 + delta_y^2)
	float delta_x = (point_b.x - point_a.x);
	float delta_y = (point_b.y - point_a.y);
	return sqrt(delta_x*delta_x + delta_y*delta_y);
}

float get_angle(Point point1, Point point2) {
	float angle = 0;
	//if (point1.x - point2.x != 0)
	if (point1.y - point2.y != 0)
		//angle = atan((point2.y - point1.y) / (point1.x - point2.x));
		angle = atan((point1.x - point2.x) / (point2.y - point1.y));
	return angle;
}

//bool overlap(Trianglelist* polygon1, Trianglelist* polygon2) {
//	return true;	// TODO
//}

float geom::angle(Point point_a, Point point_b) {
	if (point_a.x - point_b.x != 0)		// prevent division by zero
		//if (point_a.x - point_b.x < 0)
			return atan((point_a.y - point_b.y) / (point_a.x - point_b.x));
		//else
		//	return -atan((point_a.y - point_b.y) / (point_a.x - point_b.x));
	else
		return PIPER2;		// FIXME
}
