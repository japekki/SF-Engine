//#include "misc.hpp"
#include "base.hpp"
#include "gameplay.hpp"
#include "inputdevices.hpp"
#include "player.hpp"
#include "human.hpp"
#include "audio.hpp"
#include "vehicle.hpp"
#include "geom.hpp"
#include "weapon.hpp"

Player::Player(Gameplay* gameplay) {
	this->gameplay = gameplay;
	this->human = new Human();
	this->vehicle = new Rocket();
	this->vehicle->owner = this;
}

Player::~Player() {
	delete this->human;
	delete this->vehicle;
}

void Player::spawn() {
	// Spawn to first base
	// TODO: random base
	//this->location = this->bases.at(0)->location;
}

Point* Player::get_location() {
	return this->location;
}

void Player::set_location(float x, float y) {
	this->location->x = x;
	this->location->y = y;
}

void Player::move() {
	if (this->human->inside_vehicle)
		this->vehicle->move();
	else
		this->human->move();
}

void Player::add_bullet(Bullet* bullet) {
	this->bullets.push_back(bullet);
}

void Player::shoot() {
	if (this->human->inside_vehicle)
		this->vehicle->weapons.at(0)->shoot();
	else
		this->human->shoot();
	this->gameplay->audio->play(this->gameplay->sound_shoot, 1);
}

void Player::surrender() {
	// remove player from Gameplay (TODO: what to do for player's vehicles, gadgets, buildings etc.)
}

void Player::execute() {
	if (this->gameplay->keyboard->key_RIGHT_down) {
		if (this->human->inside_vehicle)
			this->vehicle->rotate(0.05);
		else
			this->human->move();
	}
	if (this->gameplay->keyboard->key_LEFT_down) {
		if (this->human->inside_vehicle)
			this->vehicle->rotate(-0.05);
		else
			this->human->move();
	}
	if (this->gameplay->keyboard->key_UP_down) {
		if (this->human->inside_vehicle)
			this->vehicle->inc_speed(5);
		else
			this->human->move();
	}
	if (this->gameplay->keyboard->key_DOWN_down) {
		if (this->human->inside_vehicle)
			this->vehicle->dec_speed(5);
		else
			this->human->move();
	}

	if (this->gameplay->keyboard->key_SPACE_down) {
		this->gameplay->keyboard->key_SPACE_down = false;
		this->shoot();
	}
}

void Team::add_base(Base* base) {
	this->bases.push_back(base);
}

void Team::add_player(Player* player) {
	this->players.push_back(player);
}

void Team::surrender() {
}
