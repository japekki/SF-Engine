#ifndef BULLET_HPP
	#define BULLET_HPP

	#include "player.hpp"
	#include "projectile.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_BULLETHIT DATAPATH "bullethit.wav"

	class Bullet : public Projectile2D {
		Player *owner;
		Bullet(Player *owner, Coordinate2D coordinate, Vector2D heading);
	};

#endif // BULLET_HPP
