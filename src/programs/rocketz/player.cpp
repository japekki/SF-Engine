//#include "misc.hpp"
#include "base.hpp"
#include "gameplay.hpp"
#include "inputdevices.hpp"
#include "player.hpp"
#include "human.hpp"
#include "audio.hpp"
#include "vehicle.hpp"
#include "geometry.hpp"
#include "weapon.hpp"
#include "space.hpp"

// TODO:
// - Player can use both joystick and keyboard
// - Many players can share the same keyboard with different buttons

Player::Player(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

Player::~Player() {
}

void Player::set_color(uint32_t color) {
	this->color = color;
}

float Player::get_health() {
	float result;
	if (human->inside_vehicle)
			result = vehicle->health;
		else
			result = human->health;
	return result;
}

float Player::get_speed() {
	float result;
	if (human->inside_vehicle)
			result = vehicle->get_speed();
		else
			result = human->get_speed();
	return result;
}

Point Player::get_location() {
	Point location;
	if (human->inside_vehicle)
			location = vehicle->location;
		else
			location = human->location;
	return location;
}

Base* Player::nearest_homebase() {
	for (uint32_t i=0; i<team->bases.size(); i++) {
		// get distance between player and team->bases[i)
		// if (distance < closest_base) closest_base = team->bases[i)
	}
	return nullptr;	// TODO
}

void Player::spawn() {
	// Spawn to random base (if any exists)
	lives--;
	if (lives > 0 and team->bases.size() > 0)
		this->set_location(team->bases[rand() % team->bases.size()]->location);
}

void Player::spawn(Base* base) {
	// Spawn to given base
	this->set_location(base->location);
}

void Player::set_location(float x, float y) {
	if (human->inside_vehicle) {
		vehicle->location.x = x;
		vehicle->location.y = y;
	}
	else {
		human->location.x = x;
		human->location.y = y;
	}
}

void Player::set_location(Point location) {
	if (human->inside_vehicle)
		vehicle->location = location;
	else
		human->location = location;
}

void Player::move() {
	if (human->inside_vehicle)
		vehicle->move();
	else
		human->move();
	// TODO: scroll this->viewarea
}

void Player::shoot(uint8_t weapon_index) {
	if (human->inside_vehicle)
		vehicle->shoot(weapon_index);
	else
		human->shoot();
}

void Player::surrender() {
	// remove player from Gameplay (TODO: what to do for player's vehicles, gadgets, buildings etc.)
}

/*
// angle to center when vehicle is:
	right	0
	left	0
	up		PIPER2, -PIPER2
	down	PIPER2, -PIPER2
// vehicle angle when tip facing to:
	right	-PIPER2
	left	PIPER2
	up		PI
	down	0
*/

void Player::execute() {
	//float angle = geom::angle(this->get_location(), Point(0,0));
	//printf("angle of vehicle: %f\n", vehicle->angle);
	//printf("angle to center: %f\n\n", angle);
	if (human->health > 0) {
		// CHECK USER INPUT:
		//if (gameplay->keyboard->key_RIGHT_down) {
		if (SDL_JoystickGetAxis(joystick->sdl_joystick, 0) > JOYSTICK_AXIS_MARGIN
		or gameplay->keyboard->buttonstates[SDL_SCANCODE_RIGHT]) {
			if (human->inside_vehicle)
				vehicle->rotate_cw();
			else
				human->walk(WALK_RIGHT);
		}

		if (SDL_JoystickGetAxis(joystick->sdl_joystick, 0) < -JOYSTICK_AXIS_MARGIN
		or gameplay->keyboard->buttonstates[SDL_SCANCODE_LEFT]) {
			if (human->inside_vehicle)
				vehicle->rotate_ccw();
			else
				human->walk(WALK_LEFT);
		}

		//float angle = get_angle(vehicle->location, Point(0,0));
		//printf("player angle to origo: %f\n", angle);

		if (SDL_JoystickGetAxis(joystick->sdl_joystick, 1) < -JOYSTICK_AXIS_MARGIN
		or gameplay->keyboard->buttonstates[SDL_SCANCODE_UP]) {
			if (human->inside_vehicle) {
				vehicle->accelerate();
			} else {
				//human->move();
			}
		}

		// TODO: option for togglable and hold-down versions:
		//if (gameplay->keyboard->buttonstates[SDL_SCANCODE_SPACE) {
		if (gameplay->keyboard->get_presscount(SDL_SCANCODE_SPACE)) {
			if (human->inside_vehicle) {
				vehicle->toggle_slowdown();
			} else {
				if (human->heading.j < 0)
					human->activate_parachute();
				if (!human->parachute_in_use)
					human->jump();
			}
		}

		//if (gameplay->keyboard->buttonstates[SDL_SCANCODE_TAB]) {
			// TODO: Slow accurate mode and fast fly mode
			// Set zoom, vehicle rotation speed
		//}

		if (gameplay->keyboard->get_presscount(SDL_SCANCODE_RETURN)) {
			if (human->inside_vehicle) {
				human->get_out_from_vehicle();
			} else {
				// Check which vehicle is nearest and get in:
				//human->get_into_vehicle(gameplay->space->get_nearest_blob(human, GAMEBLOB_VEHICLE));
				// TODO: Check if within reach / not too far
				human->get_into_vehicle(vehicle);
			}
		}

		if (joystick->get_buttonstate(joybut_shoot) or
			gameplay->keyboard->buttonstates[SDL_SCANCODE_RCTRL] or
			gameplay->keyboard->buttonstates[SDL_SCANCODE_LCTRL] or
			gameplay->keyboard->buttonstates[SDL_SCANCODE_RSHIFT] or
			gameplay->keyboard->buttonstates[SDL_SCANCODE_LSHIFT])
				this->shoot(0);
		//if (gameplay->keyboard->buttonstates[SDL_SCANCODE_RCTRL] or gameplay->keyboard->buttonstates[SDL_SCANCODE_LCTRL])
		//	this->shoot(1);
		if (human->inside_vehicle and vehicle->weapons.size() > 1)
			for (int i=1; i<vehicle->weapons.size(); i++)
				if (joystick->get_buttonstate(i + 7) or gameplay->keyboard->buttonstates[SDL_SCANCODE_1 - 1 + i])	// FIXME: use only 10 number keys
					if (i < vehicle->weapons.size())
						vehicle->shoot(i);
	}
}

void Player::set_joystick(Joystick* joystick) {
	this->joystick = joystick;

	// Set button bindings:
		if (joystick->button_amount >= 2) {
			joybut_shoot_active = 0;
			joybut_cycle_active = 1;
		}
		if (joystick->button_amount >= 3) {
			joybut_slowdown = 2;
			joybut_jump = 2;
		}
		if (joystick->button_amount == 4) {
			joybut_eject = 3;
		}
		if (joystick->button_amount >= 5) {
			joybut_shoot = 0;
			joybut_shoot_active = 1;
			joybut_cycle_active = 2;
			joybut_slowdown = 3;
			joybut_jump = 3;
			joybut_eject = 4;
		}
		if (joystick->button_amount == 8) {
			joybut_thrust = 5;
		}
		if (joystick->button_amount == 8) {
			joybut_zoomin = 6;
			joybut_zoomout = 7;
		}
		if (joystick->button_amount >= 9) {
			for (int i=9; i<joystick->button_amount; i++)
			joybut_weapons.push_back(i-1);
		}
}

Team::Team() {
}

Team::Team(std::string name) {
	this->name = name;
}

Team::~Team() {
}

void Team::add_base(Base* base) {
	bases.push_back(base);
	base->owner_team = this;
	// TODO:
	// Owner is team or player
	// base->owner = this;
}

void Team::add_player(Player* player) {
	player->team = this;
	players.push_back(player);
}

void Team::surrender() {
}

bool Team::has_human_alive() {
	bool result = false;
	for (unsigned p = 0; p<players.size(); p++)
		if (players[p]->human->health > 0)
			result = true;
	return result;
}
