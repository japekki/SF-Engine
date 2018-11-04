#ifndef SCENE_HPP
	#define SCENE_HPP

	#include "math.hpp"
	#include <vector>
	#include "entity.hpp"

	class Camera {
		public:
			vec3 location;
			vec3 direction;
			float angle_x, angle_y, angle_z;	// Viewport, "nakokentta"
			float zoom;
			void rotate(float angle_x, float angle_y, float angle_z);
			Camera();
			Camera(vec3 location_, vec3 direction_);
			// ~Camera();
	};

	class Scene {
		public:
			std::vector<Entity> entityarray;
			Camera Kamera;
			Scene();
			~Scene();
			void add_entity(Entity &Entity_);  // TODO: Palautta kahva myohempaa poistoa (tms.) varten?
			bool del_entity(Uint16 id);
			void draw(SDL_Surface *sdlsurface);
			void apply_perspective();
	};

#endif // SCENE_HPP
