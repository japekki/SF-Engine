/*
	SF-Engine

	This file has routines for making different worlds / views.
*/

// TODO:
// - Don't draw every object in the scene/world and then just clip pixels

#ifndef WORLD_HPP
	#define WORLD_HPP

	#include <vector>

	// Forward declarations:
		//class Camera;
		class Polygon3D;

	class World {
		public:
			std::vector<Polygon3D*> polygons;
			//Camera camera;
			World();
			~World();
			void add_polygon3d(Polygon3D* polygon);
			void execute();
			//void draw(SDL_Surface *sdlsurface);
			//void apply_perspective();
	};

#endif // WORLD_HPP
