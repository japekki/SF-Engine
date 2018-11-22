#ifndef ENTITY_HPP
	#define ENTITY_HPP

/*
	#include <vector>
	#include <string>
	#include "geom.hpp"
	#include "options.hpp"
*/

	struct elements {
		float a,b,c,d,e,f,g;
	};

	class Entity {
	public:
		Entity();
		~Entity();
		SDL_Surface *surface;

		string filename;

		// Physical properties:
			unsigned char dimensions;   // 1, 2, 3 (or 4?)
			point3d location;
			vec3 direction;
			vec3 rotation; // Angles by X, Y and Z axis
			elements balance;

		// Interaction properties:

		// Visual properties:
			unsigned int color;
			unsigned char polygonshadestyle;

		std::vector<Vertex2d> vertex2darray, vertex2darray_stored;
		std::vector<vertex3d_struct> vertex3darray, vertex3darray_stored;
		std::vector<unsigned int> face2darray, face2darray_stored;
		std::vector<unsigned int> face3darray, face3darray_stored;
		// TODO:
		// std::vector<geomitem> geomitemarray;
		// std::vector<> array;

		// Graphical methods:
			void resize3dvertexarray(int n);
			//void resizefacearray(int n);
			void movecenter();
			void translatevertexarray();
			void scale(float scale_x, float scale_y, float scale_z);
			void scale(float scale);
			void rotatecenter();
			void rotatecenter(float angle_x, float angle_y, float angle_z);
			void rotatevertexarray();
			void rotatevertexarray(float angle_x, float angle_y, float angle_z);
			boundingbox getboundingbox();

			void draw2d_polygon();
			void draw3d_polygon();
			void draw2d_wireframe();

		// Data methods:
			bool loadfromfile(string filename_);
			bool savetofile(string filename_);
			bool loadfromfile();
			bool savetofile();
			void pushgeom();  // Store original geometry to avoid rounding inaccuracy during serial computation
			void popgeom();   // Restore original geometry
			void generate_3dball(float r, unsigned short corners);

		// Interaction methods:
			bool connecttoentity(Entity Entiteetti);    // TODO: "Ylempi" luokka hoitaa namat?
			bool disconnectfromentity(Entity Entiteetti);
			void react(Entity entiteetti);

			void effux_sine(unsigned int time);
		#ifdef WITH_DEBUGMSG
			void printvertexarray();
		#endif

	};

#endif // ENTITY_HPP
