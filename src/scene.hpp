/*
	SF-Engine

	This file has routines for making different scenes (worlds or operation modes/views in the program.
*/

#ifndef SCENE_HPP
	#define SCENE_HPP

	#include <vector>
	#include "camera.hpp"
	#include "entity.hpp"

	// TODO:
	// - Don't draw every object in the scene/world and then just clip pixels

	class Scene {
		public:
			std::vector<Entity> entities;
			//Camera camera;
			Scene();
			~Scene();
			void add_entity(Entity entity);
			bool del_entity(unsigned short id);
			//void draw(SDL_Surface *sdlsurface);
			//void apply_perspective();
	};

#endif // SCENE_HPP
