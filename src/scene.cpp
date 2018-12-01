#include "scene.hpp"
#include "entity.hpp"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add_entity(Entity entity) {
	entities.push_back(entity);
	// TODO: return id
	// return 0;
}

bool Scene::del_entity(unsigned short id) {
}

/*
void Scene::draw(Display *display) {
	for (int i=0; i<entities.size(); i++) {
		entities.at(i).draw3d_polygon();
	}
}
*/

