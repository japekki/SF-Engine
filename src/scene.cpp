#include "scene.hpp"

Camera::Camera() {
	printf("Camera created.\n");
}

Camera::Camera(vec3 location_, vec3 direction_) {
	location = location_;
	direction = direction_;
}

void Camera::rotate(float angle_x, float angle_y, float angle_z) {
	//#ifdef WITH_OPENGL
		//glRotatef(-0.6f, 0.0f, 0.0f, 1.0f);
	//#endif
}

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add_entity(Entity &Entity_) {
	entityarray.push_back(Entity_);
	// TODO: return id
	// return 0;
}

bool Scene::del_entity(Uint16 id) {

}


void Scene::draw(SDL_Surface *sdlsurface) {
	for (int i=0; i<entityarray.size(); i++) {
		entityarray.at(i).draw3d_polygon();
	}
}

void Scene::apply_perspective() {
}
