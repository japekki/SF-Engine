#include "camera.hpp"
#include "geom.hpp"

Camera::Camera() {
}

Camera::~Camera() {
}

//void Camera::apply_perspective() {
//}

void Camera::rotate(float angle_x, float angle_y, float angle_z) {
}

void Camera::set_focus(float focus) {
	this->focus = focus;
}

void Camera::set_zoom(float zoom) {
	this->zoom = zoom;
}
