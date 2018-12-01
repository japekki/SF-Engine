/*
	SF-Engine

	This file has routines for handling complex objects.
	An entity may have a geometric shape, but also other attributes
	defining their behavior and interaction relations with other entities.
*/

#ifndef ENTITY_HPP
	#define ENTITY_HPP

	//#include <string>
	//#include <vector>

	class Entity {
		public:
			Entity();
			~Entity();

		/*
			std::string filename;
			std::vector<geomitem> geomitemarray;
			bool loadfromfile();
			bool savetofile();
			bool connecttoentity(Entity entity);
			bool disconnectfromentity(Entity entity);
			void react(Entity *entity);
		*/
	};

#endif // ENTITY_HPP
