#include "base.hpp"
#include "gameplay.hpp"
#include "audio.hpp"
#include "inputdevices.hpp"
#include "display.hpp"
#include "filenames.hpp"
#include "computerplayer.hpp"
#include "level.hpp"
#include "color.hpp"
#include "player.hpp"
#include "vehicle.hpp"
#include "bullet.hpp"
#include "human.hpp"
#include "weapon.hpp"
#include "misc.hpp"

Gameplay::Gameplay(Display *display, Audio *audio, Keyboard *keyboard, Mouse *mouse) {
	this->display = display;
	this->audio = audio;
	this->keyboard = keyboard;
	this->mouse = mouse;
}

Gameplay::~Gameplay() {
	//delete this->randomlevelgenerator;

	// DELETE LEVEL:
		delete this->level;

	// DELETE TEAMS AND PLAYERS:
		for (unsigned int t=0; t<this->teams.size(); t++) {
			for (unsigned int p=0; p<this->teams.at(t)->players.size(); p++)
				delete this->teams.at(t)->players.at(p);
			delete this->teams.at(t);
		}

	// FREE AUDIO AND STOP MUSIC:
		//if (this->with_sound)
			Mix_FreeChunk(this->sound_building_explode);
			Mix_FreeChunk(this->sound_shoot);

			this->sound_building_explode = nullptr;
			this->sound_shoot = nullptr;
}

void Gameplay::init() {

	// Randomize level
	// Randomize game objective
	// Randomize 1-8 players (1-8 for fool around or rally mode, 2-8 for the rest)

	// CREATE LEVEL:
		//this->randomlevel = new RandomLevel(1000, 1000);
		//this->randomlevel->generate();
		this->level = new Level(10000, 10000);
		//this->level->add_layer(new Layer());

	// CREATE PLAYERS:
		Player* player_human = new Player(this);
		Player* player_computer1 = new ComputerPlayer(this);
		Player* player_computer2 = new ComputerPlayer(this);

	// PUT HUMANS INSIDE VEHICLES:
		player_human->human->get_into_vehicle(player_human->vehicle);
		player_computer1->human->get_into_vehicle(player_computer1->vehicle);
		player_computer2->human->get_into_vehicle(player_computer2->vehicle);

	// SET VEHICLE COLORS:
		player_human->vehicle->polygon->set_color(COLOR_CRTGREEN);
		player_computer1->vehicle->polygon->set_color(COLOR_RED);
		player_computer2->vehicle->polygon->set_color(COLOR_BLUE);

	// SET VEHICLE WEAPONS:
		player_human->vehicle->weapons.push_back(new Weapon_laser());
		player_human->vehicle->weapons.push_back(new Weapon_teleport());
		player_computer1->vehicle->weapons.push_back(new Weapon_cannon());
		player_computer1->vehicle->weapons.push_back(new Weapon_missile());
		player_computer2->vehicle->weapons.push_back(new Weapon_mine());
		player_computer2->vehicle->weapons.push_back(new Weapon_minimissile());

	// CREATE TEAMS:
		Team* team_human = new Team();
		team_human->name = "Human team with 1 player";
		Team* team_computer = new Team();
		team_computer->name = "Computer team with 2 players";

	// CREATE TEAM BASES:
		Base* base1_human = new Base();
		Base* base2_human = new Base();
		Base* base1_computer = new Base();
		Base* base2_computer = new Base();

	// ATTACH BASES TO TEAMS:
		team_human->add_base(base1_human);
		team_human->add_base(base2_human);
		team_computer->add_base(base1_computer);
		team_computer->add_base(base2_computer);

	// START FROM BASE:
		player_human->spawn();
		player_computer1->spawn();
		player_computer2->spawn();

	// ATTACH PLAYERS TO TEAMS:
		team_human->add_player(player_human);
		team_computer->add_player(player_computer1);
		team_computer->add_player(player_computer2);

	// ATTACH TEAMS TO GAMEPLAY:
		this->teams.push_back(team_human);
		this->teams.push_back(team_computer);

	// LOAD AUDIO:
		//if (this->with_sound) {
			//this->sound_building_explode = this->audio->load_sound(FILENAME_SOUND_BUILDING_EXPLODE);
			this->sound_shoot = this->audio->load_sound(FILENAME_SOUND_SHOOT);
		//}
}

void Gameplay::execute() {

	// TODO: End gameplay if objective is achieved

	// EXECUTE ALL PLAYERS:
		for (unsigned int t=0; t<this->teams.size(); t++)
			for (unsigned int p=0; p<this->teams.at(t)->players.size(); p++)
				this->teams.at(t)->players.at(p)->execute();

	// MOVE STUFF:

		// Move bullets:
			// Move players bullets:
				//for (unsigned int p=0; p<this->players.size(); p++)
				//	for (unsigned int b=0; b<this->players.at(p)->bullets.size(); b++)
				//		this->players.at(p)->bullets.at(b)->move();
			// Move rogues bullets:
				//for (int r=0; r<this->rogues.size(); r++)
					//this->rogues->bullets.at(i).move();

		// Move vehicles:

		// Move rogues:

	// TODO: Check if bullet hits

	// CHECK INPUT:

		if (this->mouse->wheel_up) {
			this->mouse->wheel_up = false;
			this->display->grid.zoom(0.9);
		}
		if (this->mouse->wheel_down) {
			this->mouse->wheel_down = false;
			this->display->grid.zoom(1.1);
		}

			// Test:
				//if (this->players.at(0)->bullets.size() % 10 == 9)
				//	this->audio->play(sound_building_explode, 1);

	// DRAW STUFF:

		SDL_SetRenderDrawColor(this->display->sdlrenderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
		this->display->clearscreen();
		// Draw level:
			// Draw parallax background:
				//for (unsigned int layernum = 0; layernum < this->gameplay->level->layers.size(); layernum++) {
					// Calculate offset where to draw texture from
					// draw texture this->gameplay->level->backgrounds[layernum];
				//}

			// Draw player vehicles:
				for (unsigned int t=0; t<this->teams.size(); t++)
					for (unsigned int p=0; p<this->teams.at(t)->players.size(); p++)
						this->display->draw_polygon(this->teams.at(t)->players.at(p)->vehicle->polygon);

			// Draw bullets:
				for (unsigned int t=0; t<this->teams.size(); t++)
					for (unsigned int p = 0; p < this->teams.at(t)->players.size(); p++)
						for (unsigned int b = 0; b < this->teams.at(t)->players.at(p)->bullets.size(); b++)
							this->teams.at(t)->players.at(p)->bullets.at(b)->move();

				//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
				//}

			// Draw rogues:
				// TODO
}

bool Gameplay::load_state() {
	return false;	// TODO
}

bool Gameplay::save_state() {
	return false;	// TODO
}

void Selfplay::init() {
}
