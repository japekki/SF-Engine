#include "fire.hpp"
// TODO: Wind

Spark::Spark(Gameplay* gameplay) : Gameblob(gameplay) {
	can_collide = false;
}

Fire::Fire(Gameplay* gameplay) : Gameblob(gameplay) {
	can_collide = false;
}
