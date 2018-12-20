#ifndef BULLET_HPP
	#define BULLET_HPP

	#include "gameobject.hpp"

	// Forward declarations:
		class Player;

	class Bullet : public Gameobject {
		public:
			//Bullet(Player *owner, Point coordinate, Vector2D heading);
			Bullet();
			~Bullet();
	};

#endif // BULLET_HPP
