#include "base.hpp"
#include "filenames.hpp"
#include "gameplay.hpp"
#include "audio.hpp"
#include "inputdevices.hpp"
#include "display.hpp"
#include "player.hpp"
#include "computerplayer.hpp"
#include "netplayer.hpp"
#include "level.hpp"
#include "color.hpp"
#include "vehicle.hpp"
#include "human.hpp"
#include "weapon.hpp"
#include "misc.hpp"
#include "color.hpp"
#include "gauge.hpp"
#include "item.hpp"

Gameplay::Gameplay(Display* display, Audio* audio, Jukebox* jukebox, Keyboard* keyboard, Mouse* mouse, Joystick* joystick) {
	this->statevideo = new Statevideo();
	this->display = display;
	this->audio = audio;
	this->jukebox = jukebox;
	this->keyboard = keyboard;
	this->mouse = mouse;
	this->joystick = joystick;

	font_glasstty_tiny = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/64);
	font_glasstty_small = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/40);
	font_glasstty_big = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/20);

	// LOAD AUDIO:
		// TODO: Don't load files if sound is disabled
		//if (with_audio) {
			//sound_building_explode = audio->load_sound(FILENAME_SOUND_BUILDING_EXPLODE);
			sound_hit = audio->load_sound(FILENAME_SOUND_HIT);
			sound_scream = audio->load_sound(FILENAME_SOUND_SCREAM);
			sound_shoot = audio->load_sound(FILENAME_SOUND_SHOOT);
			sound_explosion = audio->load_sound(FILENAME_SOUND_EXPLOSION);
			sound_radialgun = audio->load_sound(FILENAME_SOUND_RADIALGUN);
			set_volume_sfx(volume_sfx);

	// CREATE STATIC TEXTUAL TEXTURES:
		texture_gameover = new Simplesprite(grapher::create_textline_texture(display->renderer, "GAME OVER", font_glasstty_big, SDLCOLOR_GREEN));
		texture_pause = new Simplesprite(grapher::create_textline_texture(display->renderer, "PAUSE", font_glasstty_big, SDLCOLOR_GREY));
		texture_help = grapher::create_textmultiline_texture(display->renderer, helptext, font_glasstty_tiny, SDLCOLOR_YELLOW);

	game.type = GAME_TYPE_SINGLEMATCH;
}

Gameplay::~Gameplay() {

	// DELETE LEVEL:
		delete level;
		delete gamespace;

	// DELETE TEAMS AND PLAYERS:
		for (uint32_t t=0; t<teams.size(); t++) {
			for (uint32_t p=0; p<teams[t]->players.size(); p++) {
				delete teams[t]->players[p];
			}
			delete teams[t];
		}

	// STOP PLAYING / DELETE AUDIO:
		//if (with_audio)
			//Mix_FreeChunk(sound_building_explode);
			if (sound_hit != nullptr) Mix_FreeChunk(sound_hit);
			if (sound_scream != nullptr) Mix_FreeChunk(sound_scream);
			if (sound_shoot != nullptr) Mix_FreeChunk(sound_shoot);
			if (sound_explosion != nullptr) Mix_FreeChunk(sound_explosion);
			if (sound_radialgun != nullptr) Mix_FreeChunk(sound_radialgun);
			jukebox->stop();

	// DELETE FONTS:
		//delete font_glasstty_tiny;
		//delete font_glasstty_small;
		//delete font_glasstty_big;

	// DELETE TEXTURES:
		delete texture_gameover;
		delete texture_pause;
		SDL_DestroyTexture(texture_help);

	// DELETE STATE RECORD:
		delete statevideo;
}

void Gameplay::set_volume_sfx(Uint8 volume) {
		if (sound_hit != nullptr)
			sound_hit->volume = volume;
		if (sound_scream != nullptr)
			sound_scream->volume = volume;
		if (sound_shoot != nullptr)
			sound_shoot->volume = volume;
		if (sound_explosion != nullptr)
			sound_explosion->volume = volume;
		if (sound_radialgun != nullptr)
			sound_radialgun->volume = volume;
}

void Gameplay::create_random_computers(int players, int team_amount) {
	// CREATE TEAMS WITH BASES FOR GAMEPLAY:
	int teams_before = teams.size();
		for (int i=0; i<team_amount; i++) {
			teams.push_back(new Team());
			Base* base = new Base(this);
			base->location = Point(rand() % int(gamespace->width) - gamespace->width / 2, rand() % int(gamespace->height) - gamespace->height / 2);
			teams[i]->add_base(base);
		}

	// CREATE PLAYERS FOR GAMEPLAY:
		for (int i = 0; i<players; i++) {
			Player* player = new ComputerPlayer(this);
			// CREATE HUMAN AND VEHICLE:
				Vehicle* vehicle = new Rocket(this);
				vehicle->owner = player;
				Human* human = new Human(this);
				human->owner = player;
				human->get_into_vehicle(vehicle);
				player->vehicle = vehicle;
				player->human = human;
				uint32_t color = ((rand() * rand()) & 0xffffff) + 0xff000000; // TODO: RAND_MAX
				player->set_color(color);
				player->vehicle->set_color(color);
			// SET VEHICLE WEAPONS:
				// TODO: Randomize weapons
				Weapon* weapon = new Weapon(this);
				weapon->gameplay = this;
				weapon->owner = player;
				player->vehicle->weapons.push_back(weapon);

				weapon = new Weapon_spraygun(this);
				weapon->gameplay = this;
				weapon->owner = player;
				player->vehicle->weapons.push_back(weapon);

				weapon = new Weapon_radialgun(this);
				weapon->gameplay = this;
				weapon->owner = player;
				player->vehicle->weapons.push_back(weapon);

				//weapon = new Weapon_laser(this);
				//weapon->gameplay = this;
				//weapon->owner = player;
				//player->vehicle->weapons.push_back(weapon);

			// ATTACH PLAYER TO TEAM:
				int team_index = (team_amount/players*i) + teams_before;
				teams[team_index]->add_player(player);	// TODO
			// SPAWN PLAYER TO BASE:
				player->spawn();
		}
}

void Gameplay::setup_demoplay() {

	SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_NONE);

	display->with_fade = false;

	demoplay = true;

	gamespace = new Gamespace(this);
	uint16_t size = 100 + 100 * (rand() % 10);
	gamespace->width = size;
	gamespace->height = size;
	//gamespace->wall_type = 1 + rand() % 4;
	gamespace->wall_type = EDGE_TYPE_BOUNCE;

	level = new Level(this, size, size, true);
	level->randomize();
	level->rain_amount = 1;

	display->grid.set(display->width, display->height, -level->get_width()/2, level->get_width()/2, -level->get_height()/2, level->get_height()/2);

	this->create_random_computers(size/50, size/50);

	// ADD PLAYER BLOBS TO SPACE:
		for (uint32_t t=0; t<teams.size(); t++) {
			for (uint32_t b=0; b<teams[t]->bases.size(); b++)
				gamespace->add_blob(teams[t]->bases[b]);
			for (uint32_t p=0; p<teams[t]->players.size(); p++) {
				gamespace->add_blob(teams[t]->players[p]->human);
				gamespace->add_blob(teams[t]->players[p]->vehicle);
			}
		}

	if (play_music) {
		jukebox->random_tune();
	}
}

void Gameplay::setup_gameplay() {

	SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_NONE);

	display->with_fade = false;

	demoplay = false;

	gamespace = new Gamespace(this);
	uint16_t size = 100 + 100 * (rand() % 10);
	gamespace->width = size;
	gamespace->height = size;
	//gamespace->wall_type = 1 + rand() % 4;
	gamespace->wall_type = EDGE_TYPE_BOUNCE;

	level = new Level(this, size, size, true);
	level->randomize();
	level->rain_amount = 1;

	display->grid.set(display->width, display->height, -level->get_width()/2, level->get_width()/2, -level->get_height()/2, level->get_height()/2);

	Player* player_human = new Player(this);
		// Create player human and vehicle:
			Vehicle* vehicle = new Rocket(this);
			vehicle->owner = player_human;
			Human* human = new Human(this);
			human->owner = player_human;
			human->get_into_vehicle(vehicle);
			player_human->vehicle = vehicle;
			player_human->human = human;
	uint32_t color = ((rand() * rand()) & 0xffffff) + 0xff000000; // TODO: RAND_MAX
	player_human->set_color(color);
	player_human->vehicle->set_color(color);
	player_human->set_joystick(joystick);

	// SET VEHICLE WEAPONS:
		Weapon* weapon = new Weapon(this);
		weapon->gameplay = this;
		weapon->owner = player_human;
		player_human->vehicle->weapons.push_back(weapon);

		weapon = new Weapon_spraygun(this);
		weapon->gameplay = this;
		weapon->owner = player_human;
		player_human->vehicle->weapons.push_back(weapon);

		weapon = new Weapon_radialgun(this);
		weapon->gameplay = this;
		weapon->owner = player_human;
		player_human->vehicle->weapons.push_back(weapon);

		weapon = new Weapon_laser(this);
		weapon->gameplay = this;
		weapon->owner = player_human;
		player_human->vehicle->weapons.push_back(weapon);

		weapon = new Weapon_watergun(this);
		weapon->gameplay = this;
		weapon->owner = player_human;
		player_human->vehicle->weapons.push_back(weapon);

		Team* team_human = new Team();
		team_human->name = "Human team with 1 player";
		Base* base = new Base(this);
		base->location = Point(rand() % int(gamespace->width) - gamespace->width / 2, rand() % int(gamespace->height) - gamespace->height / 2);
		team_human->add_base(base);
		team_human->add_player(player_human);
		player_human->spawn();

	// ATTACH HUMAN TEAM TO GAMEPLAY:
		teams.push_back(team_human);

	this->create_random_computers(size/100, size/100);

	// ADD PLAYER BLOBS TO SPACE:
		for (uint32_t t=0; t<teams.size(); t++) {
			for (uint32_t b=0; b<teams[t]->bases.size(); b++)
				gamespace->add_blob(teams[t]->bases[b]);
			for (uint32_t p=0; p<teams[t]->players.size(); p++) {
				gamespace->add_blob(teams[t]->players[p]->human);
				gamespace->add_blob(teams[t]->players[p]->vehicle);
			}
		}

	if (play_music) {
		jukebox->random_tune();
	}
}

void Gameplay::create_debree() {
	//Blob_polygon* asteroid = new Blob_polygon;
	Bullet* asteroid = new Bullet(this);
	asteroid->owner = nullptr;	// this->owner;
	asteroid->location = Point(0, 0);
	asteroid->heading = {0, 0.1 * float(rand() % 10)};
	asteroid->heading.rotate(float(rand()));
	gamespace->add_blob(asteroid);
}

void Gameplay::spawn_items() {
	// Create new items to space:
		Item* item = nullptr;

		switch (rand() % 4) {		// TODO: Randomize item type/class
			case 0:
				item = new Item_money(this);
				break;
			case 1:
				item = new Item_medkit(this);
				break;
			case 2:
				item = new Item_extralife(this);
				break;
			case 3:
				item = new Item_fuel(this);
				break;
		}

		// Set to random location:
			item->location.x = (rand() % level->get_width()) - level->get_width() / 2;
			item->location.y = (rand() % level->get_height()) - level->get_height() / 2;

		// Add to space:
			gamespace->add_blob(item);

		// Add to gameplay:
			//this->add_item(item);
}

void Gameplay::set_grid() {
	Point location = highlighted_player->get_location();

			display->grid.set_center(location);
			if (highlighted_player->human->inside_vehicle)
				display->grid.set_zoom(1);
			else
				display->grid.set_zoom(4);

	// Snap space edge to screen edge:

	float viewarea_width = 300 + highlighted_player->get_speed() * 50;
	float viewarea_height = viewarea_width;	// TODO
	display->grid.set(display->width, display->height,
		location.x - viewarea_width/2, location.x + viewarea_width/2,
		location.y - viewarea_height/2, location.y + viewarea_height/2
	);

}

void Gameplay::resize() {
	//if (font_glasstty_tiny != nullptr)
		//delete font_glasstty_tiny;
	//if (font_glasstty_small != nullptr)
		//delete font_glasstty_small;
	//if (font_glasstty_big != nullptr)
		//delete font_glasstty_big;

	font_glasstty_tiny = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/64);
	font_glasstty_small = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/40);
	font_glasstty_big = grapher::load_font(FILENAME_FONT_GLASSTTY, display->get_width()/20);

	if (texture_gameover != nullptr)
		delete texture_gameover;
	if (texture_pause != nullptr)
		delete texture_pause;
	if (texture_help != nullptr)
		SDL_DestroyTexture(texture_help);

	texture_gameover = new Simplesprite(grapher::create_textline_texture(display->renderer, "GAME OVER", font_glasstty_big, SDLCOLOR_GREEN));
	texture_pause = new Simplesprite(grapher::create_textline_texture(display->renderer, "PAUSE", font_glasstty_big, SDLCOLOR_GREY));
	texture_help = grapher::create_textmultiline_texture(display->renderer, helptext, font_glasstty_tiny, SDLCOLOR_YELLOW);

	this->set_grid();
}

bool Gameplay::execute() {

	bool gameplay_finished = false;

	if (play_music and !Mix_PlayingMusic()) {
		//jukebox->next_tune();
		jukebox->random_tune();
	}

	Team* randomteam = teams[display->framecounter/500 % teams.size()];

	// Select player to highlight:
		if (demoplay)
			highlighted_player = randomteam->players[display->framecounter/500 % randomteam->players.size()];
		else
			highlighted_player = teams[0]->players[0];
		// TODO: Ignore expired players

	if (display->is_resized())
		this->resize();
	set_grid();	// FIXME: zooms out even when no speed (speed is altered by level blocks)

	if (level->odds_newitem > 0 and (rand() % level->odds_newitem == 0))
		this->spawn_items();

	// Create debree;
		//if (rand() % level->odds_debree == 0)
			//this->create_debree();

	// EXECUTE ALL PLAYERS:
		for (uint32_t t=0; t<teams.size(); t++)
			for (uint32_t p=0; p<teams[t]->players.size(); p++)
					teams[t]->players[p]->execute();

	// TODO: Execute rogues

	// Execute space:
		gamespace->apply_gravity();
		gamespace->apply_blackholes();
		gamespace->apply_airresistance();	// TODO: Level block alters air resistance
		gamespace->age();
		level->execute();
		gamespace->dispose_expired_gameblobs();
		//gamespace->add_new_blobs();
		// TODO: delete objects (bullet and item pointers lost?)
		gamespace->move_blobs();

		if (gamespace->apply_collisions())
			if (play_sound)
				audio->play(sound_hit, 0);

		if (play_sound) {
			if (play_explosion) {
				audio->play(sound_explosion, 0);
				play_explosion = false;
			}
			if (play_radialgun) {
				audio->play(sound_radialgun, 0);
				play_radialgun = false;
			}
			if (play_scream) {
				audio->play(sound_scream, 0);
				play_scream = false;
			}
			if (play_shoot) {
				audio->play(sound_shoot, 0);
				play_shoot = false;
			}
		}

	// CHECK INPUT:
		if (keyboard->get_presscount(SDL_SCANCODE_ESCAPE)) {
			gameover = true;
			for (int t = 0; t < teams.size(); t++)
				for (int p = 0; p < teams[t]->players.size(); p++)
					teams[t]->players[p]->vehicle->explode();
			if (delay_gameover > 1 and delay_gameover < 255)
				delay_gameover = 1;
		}
		if (keyboard->buttonstates[SDL_SCANCODE_KP_PLUS]) {		// TODO: Regular + button (not keypad)
			display->grid.zoom(4);
		}
		if (keyboard->buttonstates[SDL_SCANCODE_KP_MINUS]) {	// TODO: Regular - button (not keypad)
			display->grid.zoom(1.0/4);
		}

		if (play_music) {
			if (keyboard->get_presscount(SDL_SCANCODE_PAGEUP))
				jukebox->next_tune();
			if (keyboard->get_presscount(SDL_SCANCODE_PAGEDOWN))
				jukebox->previous_tune();
			if (keyboard->get_presscount(SDL_SCANCODE_HOME))
				jukebox->first_tune();
			if (keyboard->get_presscount(SDL_SCANCODE_END))
				jukebox->last_tune();
			if (keyboard->get_presscount(SDL_SCANCODE_DELETE))
				jukebox->random_tune();
			if (keyboard->get_presscount(SDL_SCANCODE_INSERT))
				jukebox->restart_tune();
		}
		if (keyboard->get_presscount(SDL_SCANCODE_TAB))
			view_info = !view_info;
		if (keyboard->get_presscount(SDL_SCANCODE_H))
			view_help = !view_help;
		if (keyboard->get_presscount(SDL_SCANCODE_S))
			play_sound = !play_sound;

		if (keyboard->get_presscount(SDL_SCANCODE_M)) {
			play_music = !play_music;
			if (play_music)
				jukebox->random_tune();
			else
				jukebox->stop();
		}



	// DRAW STUFF:

		// CLEAR:
			SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
			display->clearscreen();

		if (level->with_blocks) {
			// DRAW LEVEL BLOCKS:
				Point startpoint(float(level->get_width()) / -2, float(level->get_height()) / -2);
				startpoint = display->grid.transform(startpoint);
				Point endpoint(float(level->get_width()) / 2, float(level->get_height()) / 2);
				endpoint = display->grid.transform(endpoint);
				int scaled_width = endpoint.x - startpoint.x;
				int scaled_height = endpoint.y - startpoint.y;
				grapher::draw_texture(display->renderer, level->block_texture, startpoint.x, startpoint.y, scaled_width, scaled_height);
		}


	if (!level->with_blocks) {

		// DRAW GRID LINES:
			for (int x = -gamespace->width/2; x <= gamespace->width/2; x += gamespace->width/10) {
				Point a(x, -gamespace->height/2);
				Point b(x, gamespace->height/2);
				display->grid_draw_line(a, b, 0x70, 0x30, 0x80, 0x80);
			}
			for (int y = -gamespace->height/2; y <= gamespace->height/2; y += gamespace->height/10) {
				Point a(-gamespace->width/2, y);
				Point b(gamespace->width/2, y);
				display->grid_draw_line(a, b, 0x70, 0x30, 0x80, 0x80);
			}

			Point ul(-gamespace->width/2, -gamespace->height/2);
			Point ur(gamespace->width/2, -gamespace->height/2);
			Point dl(-gamespace->width/2, gamespace->height/2);
			Point dr(gamespace->width/2, gamespace->height/2);

			Point origo(0, 0);
			origo = display->grid.transform(origo);
			SDL_SetRenderDrawColor(display->renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(display->renderer, origo.x-1, origo.y);
			SDL_RenderDrawPoint(display->renderer, origo.x+1, origo.y);
			SDL_RenderDrawPoint(display->renderer, origo.x, origo.y-1);
			SDL_RenderDrawPoint(display->renderer, origo.x, origo.y+1);
			SDL_RenderDrawPoint(display->renderer, origo.x, origo.y);
	}


	// DRAW ALL BLOBS:
		for (uint32_t i=0; i<gamespace->blobs.size(); i++) {
			gamespace->blobs[i]->draw();
		}

	if (view_info) {
		// DRAW GUIDELINE TO ALL ENEMIES:
			for (uint32_t t=0; t<teams.size(); t++)
				for (uint32_t p=0; p<teams[t]->players.size(); p++) {
					Player* player = teams[t]->players[p];
					if (player != highlighted_player and player->team != highlighted_player->team)
						display->grid_draw_line(highlighted_player->get_location(), player->get_location(), player->color + 0x40000000);
				}

		// Count maximum amount of simultaneous items:
			if (gamespace->blobs.size() > gamespace->max_blobs)
				gamespace->max_blobs = gamespace->blobs.size();

		// DRAW TEXT WINDOW:
			int y = 10;
			int x = 10;
            display->draw_text("FPS: " + std::to_string(int(display->get_fps_last())) + "/" + std::to_string(display->fps_desired), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 40;
			display->draw_text("Blobs: " + std::to_string(gamespace->blobs.size()), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 20;
			display->draw_text("Max blobs: " + std::to_string(gamespace->max_blobs), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 20;
			display->draw_text("Total blobs: " + std::to_string(gamespace->total_blobs), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 40;
			display->draw_text("Collisions: " + std::to_string(gamespace->collisions), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 20;
			display->draw_text("Max collisions: " + std::to_string(gamespace->max_collisions), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 20;
			display->draw_text("Total collisions: " + std::to_string(gamespace->total_collisions), font_glasstty_tiny, SDLCOLOR_GREEN1, x, y);
			y += 40;
			for (uint32_t t=0; t<teams.size(); t++) {
				for (uint32_t p=0; p<teams[t]->players.size(); p++) {
					Player* player = teams[t]->players[p];
					display->draw_text("Team " + std::to_string(t+1) + " Player " + std::to_string(p+1), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					std::string insidevehicletext = "Inside Vehicle: ";
					if (player->human->inside_vehicle)
						insidevehicletext += "Yes";
					else
						insidevehicletext += "No";
					display->draw_text(insidevehicletext, font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Human Health: " + std::to_string(int(player->human->health)), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Vehicle Health: " + std::to_string(int(player->vehicle->health)), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Fuel: " + std::to_string(player->vehicle->get_fuel()), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Air: " + std::to_string(player->human->air_left), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Vehicle Speed: " + std::to_string(int(player->vehicle->get_speed()*50)), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 20;
					display->draw_text("Vehicle Max Speed: " + std::to_string(int(player->vehicle->get_max_speed()*50)), font_glasstty_tiny, color::UintToSDLColor(player->color), x, y);
					y += 40;
					// TODO: Draw gauges
						//Gauge* testgauge = new Gauge(this);
						//testgauge->maximum = 100;
						//testgauge->width = 100;
						//testgauge->height = 100;
						//testgauge->value = player->get_health();
						//testgauge->draw(10, 10);
				}
			}
		} else if (view_help) {
			// DRAW HELP:
				// FIXME: Leaks memory:
					//texture_help = grapher::create_textmultiline_texture(display->renderer, helptext, font_glasstty_tiny, SDLCOLOR_YELLOW);
					//grapher::draw_texture(display->renderer, texture_help, 0, 0);
					//SDL_DestroyTexture(texture_help);
				// FIXME:
					//display->draw_text(helptext, font_glasstty_small, SDLCOLOR_YELLOW, 0, 0);
				grapher::draw_texture(display->renderer, texture_help, 0, 0);
		}

	// Save current state:
		//statevideo->record(state)

		// TODO: End gameplay if objective is reached

	uint8_t teams_left = 0;

	// End game when only one team has at least one human left:
		for (uint32_t t=0; t<teams.size(); t++) {
			if (teams[t]->has_human_alive())
				teams_left++;
		}
		if (teams_left < 2)
			gameover = true;

	if (gameover) {
		// Center text on screen:
			texture_gameover->rect.x = (display->width - texture_gameover->rect.w) / 2;
			texture_gameover->rect.y = (display->height - texture_gameover->rect.h) / 2;
			// TODO: Separate routine for this
		display->draw_texture(texture_gameover);
		if (--delay_gameover == 0)
			gameplay_finished = true;
	}

	return gameplay_finished;
}

State* Gameplay::get_state() {
	State* state = new State();
	state->timeindex = display->get_framecount();
	//for (uint8_t t=0; t<teams.size(); t++)
		//state->teams
	return state;
}

bool Gameplay::retry_from_frame(int framenumber) {
	// Play old game again from given frame
		// Delete current gameplay (or store it)
		// Create new gameplay
		// Set state and time
		// Start gameplay
	return false;
}

void Gameplay::add_item(Item* item) {
	items.push_back(item);
}

//bool State::load(const char* filename) {
//	return false;	// TODO
//}

//bool State::save(const char* filename) {
//	return false;	// TODO
//}

Statevideo::Statevideo() {
}

Statevideo::~Statevideo() {
}

void Statevideo::record_state(State* state) {
	//this->state = STATE_RECORDING;
	// Read timestamp
	// Read level parameters
	// Read gameplay parameters
	// Read player parameters
	// Read blobs
}

void Statevideo::play() {
	//state = STATE_PLAYING;
}

void Statevideo::stop() {
	//state = STATE_IDLE;
}

bool Statevideo::load(const char* filename) {
	return false;	// TODO
}

bool Statevideo::save(const char* filename) {
	return false;	// TODO
}

bool Statevideo::set_position(){
	return false;	// TODO
}

bool Statevideo::seek_frames(int frames){
	return false;		// TODO
}

bool Statevideo::seek_time(int time){
	return false;		// TODO
}

State* Statevideo::next() {
	return nullptr;		// TODO
}

State* Statevideo::previous() {
	return nullptr;		// TODO
}

/*
TODO:

Ask from player when creating new gameplay:

Select teams and players
	Select human
	Select vehicle
	Select weapons
	Select shield
Select level
	Select size
	Select blocks
	Select border (wall and roof) type
	Select objective
	Select weather
*/
