#include "misc.hpp"
#include "gamespace.hpp"
#include "gameplay.hpp"
#include "block.hpp"
#include "level.hpp"
#include "explosion.hpp"
#include "item.hpp"

Gameblob::Gameblob(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

Gameblob::~Gameblob() {
}

void Gameblob::age() {
	if (can_expire and expirecounter > 0)
		expirecounter--;
}

void Gameblob::explode() {
	if (health > 0)
		health = 0;
	this->can_expire = true;
	this->expirecounter = 0;
	switch (type) {
		case GAMEBLOB_TYPE_VEHICLE:
			gameplay->play_explosion = true;
			Explosion explosion(gameplay);
			explosion.create_sparks(location, heading, mass/2, mass);
			break;
		//case GAMEBLOB_HUMAN:
			//die();
			//break;
	}
}

void Gameblob::draw() {
	//log("Gameblob::draw()\n");
	if (trail->get_length() > 1)
	for (uint32_t i=0; i<trail->get_length()-1; i++)
		gameplay->display->grid_draw_line(trail->points[i], trail->points[i+1], 0x60, 0, 0, 0x80);
}

void Gameblob::heal(float health) {
	this->health += health;
	if (this->health > this->max_health)
		this->health = this->max_health;	// TODO: leave some health left into medkit
}

void Gameblob::damage(float damage) {
	if (health > 0) {	// Prevent multiple explosions
		health -= damage;
		if (health <= 0) {
			can_expire = true;
			expirecounter = 0;
			explode();	// Vehicle, building
			//die();		// Human
		}
	}
}

void Gameblob::use_item(Item* item) {
	//log("Gameblob::use_item()");
	item->expirecounter = 0;
}

Gamespace::Gamespace(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

Gamespace::~Gamespace() {
	for (int i=0; i<blobs.size(); i++)
		delete blobs[i];
}

void Gamespace::add_blob(Gameblob* blob) {
	blobs.push_back(blob);
	total_blobs++;
}

//void Gamespace::add_new_blobs() {
//	blobs.insert(std::end(blobs), std::begin(new_blobs), std::end(new_blobs));
//	total_blobs += new_blobs.size();
//	new_blobs.clear();
//}

void Gamespace::move_blobs() {
	for (uint32_t i=0; i<blobs.size(); i++) {

		if (!blobs[i]->is_expired()) {
			blobs[i]->move();

		//int blockindex = width * blobs[i)->location.y + blobs[i)->location.x;
		// convert grid coordinates into block pixels
		// If blob hits land, delete blob and put air there
		 //if (gameplay->level->blocks[blockindex] == BLOCK_LAND) {
		//	gameplay->level->blocks[blockindex] = BLOCK_AIR;
			//delete blobs[i);
			//blobs.erase(blobs.begin() + i);
		//} else {

		// If blob hits left wall:
			if (blobs[i]->location.x < -this->width/2) {
				//blobs[i]->location.x = -this->width/2;		// If beyond space edge, move onto edge
				if (blobs[i]->type == GAMEBLOB_TYPE_BULLET) {
					switch (wall_type) {
						case EDGE_TYPE_BOUNCE:
							// If bullet, bounce:
								blobs[i]->location.x = -this->width/2;
								blobs[i]->heading.i *= -0.5;
							break;
						case EDGE_TYPE_DELETE:
							// If bullet, delete:
								blobs[i]->can_expire = true;
								blobs[i]->expirecounter = 0;
							break;
						case EDGE_TYPE_STOP:
							// If bullet, stop:
								blobs[i]->heading.i = 0;
							break;
						case EDGE_TYPE_LOOP:
							// If bullet, warp to the opposite space edge:
								blobs[i]->location.x += this->width;
							break;
					}
				} else {
					// Else stop to wall:
						blobs[i]->heading.i = 0;
						blobs[i]->location.x = -this->width/2;
				}
			}

			// If blob hits right wall:
			if (blobs[i]->location.x >= this->width/2) {
				//blobs[i]->location.x = this->width/2;
				if (blobs[i]->type == GAMEBLOB_TYPE_BULLET) {
					switch (wall_type) {
						case EDGE_TYPE_BOUNCE:
							// If bullet, bounce:
								blobs[i]->location.x = this->width/2;
								blobs[i]->heading.i *= -0.5;
							break;
						case EDGE_TYPE_DELETE:
							// If bullet, delete:
								blobs[i]->can_expire = true;
								blobs[i]->expirecounter = 0;
							break;
						case EDGE_TYPE_STOP:
							// If bullet, stop:
								blobs[i]->heading.i = 0;
							break;
						case EDGE_TYPE_LOOP:
							// If bullet, warp to the opposite space edge:
								blobs[i]->location.x -= this->width;
							break;
					}
				} else {
					// Else stop to wall:
						blobs[i]->heading.i = 0;
						blobs[i]->location.x = this->width/2;
				}
			}

			// If blob hits ceiling:
			if (blobs[i]->location.y < -this->height/2) {
				blobs[i]->location.y = -this->height/2;
				if (blobs[i]->type == GAMEBLOB_TYPE_BULLET) {
					switch (ceiling_type) {
						case EDGE_TYPE_BOUNCE:
							// If bullet, bounce:
								blobs[i]->location.y = -this->height/2;
								blobs[i]->heading.j *= -0.5;
							break;
						case EDGE_TYPE_DELETE:
							// If bullet, delete:
								blobs[i]->can_expire = true;
								blobs[i]->expirecounter = 0;
							break;
						case EDGE_TYPE_STOP:
							// If bullet, stop:
								blobs[i]->heading.j = 0;
							break;
						case EDGE_TYPE_LOOP:
							// If bullet, warp to the opposite space edge:
								blobs[i]->location.y += this->height;
							break;
					}
				} else {
					// Else stop to ceiling:
						blobs[i]->heading.j = 0;
						blobs[i]->location.y = -this->height/2;
				}
			}

			// If blob hits floor:
			if (blobs[i]->location.y > this->height/2) {
				blobs[i]->location.y = this->height/2;
					if (blobs[i]->type == GAMEBLOB_TYPE_BULLET) {
						switch (floor_type) {
							case EDGE_TYPE_BOUNCE:
								// If bullet, bounce:
									blobs[i]->location.y = this->width/2;
									blobs[i]->heading.j *= -0.5;
								break;
							case EDGE_TYPE_DELETE:
								// If bullet, delete:
									blobs[i]->can_expire = true;
									blobs[i]->expirecounter = 0;
								break;
							case EDGE_TYPE_STOP:
								// If bullet, stop:
									blobs[i]->heading = Vector(0, 0);
								break;
							case EDGE_TYPE_LOOP:
							// If bullet, warp to the opposite space edge:
								blobs[i]->location.y -= this->height;
							break;
						}
					} else {
						// Else stop to floor:
							blobs[i]->heading.j = 0;
							blobs[i]->location.y = this->height/2;
					}
			}
		}
	}
}

void Gamespace::apply_gravity() {
	//log("Space::apply_gravity()");
	for (uint32_t i=0; i<blobs.size(); i++) {
		// Fall down:
			blobs[i]->heading.j += gravity;
		// TODO: Each blob attracts each blob
	}
}

void Gamespace::apply_airresistance() {
	//log("Space::apply_airresistance()");
	for (uint32_t i=0; i<blobs.size(); i++) {
		blobs[i]->heading.i *= airresistance;
		blobs[i]->heading.j *= airresistance;
	}
}

uint32_t Gamespace::apply_collisions() {
	// Also collects items
	collisions = 0;
	if (collision_type == COLLISION_TYPE_NORMAL) {
		if (blobs.size() > 1) {
			for (uint32_t a=0; a<blobs.size(); a++) {
				if (blobs[a]->can_collide) {
					for (uint32_t b=a+1; b<blobs.size(); b++) {
						Gameblob* blob_a = blobs[a];
						Gameblob* blob_b = blobs[b];
						if (blob_b->can_collide) {
							if (get_distance(blob_a->location, blob_b->location) < blob_a->collision_radius + blob_b->collision_radius) {

								// Collision is happening

								// If other blob is an item and the other is collector:
									if (blob_a->can_collect and blob_b->type == GAMEBLOB_TYPE_ITEM) {
										//log("blob_a->use_item(blob_b)");
										//blob_a->use_item(blob_b);
									}
									else if (blob_b->can_collect and blob_a->type == GAMEBLOB_TYPE_ITEM) {
										//log("blob_b->use_item(blob_a)");
										//blob_b->use_item(blob_a);
									}

								// If other blob is base and the other is owner's Human or Vehicle, do not collide:
									else if (blob_a->type == GAMEBLOB_TYPE_BASE and
										(blob_b->type == GAMEBLOB_TYPE_HUMAN or blob_b->type == GAMEBLOB_TYPE_VEHICLE)) {
											// stop vehicle and set rotation
											// increase health, fuel, shield and weapons
											//log("TODO: Docking...\n");
									}
									else if (blob_b->type == GAMEBLOB_TYPE_BASE and
										(blob_a->type == GAMEBLOB_TYPE_HUMAN or blob_a->type == GAMEBLOB_TYPE_VEHICLE)) {
											// stop vehicle and set rotation
											// increase health, fuel, shield and weapons
											//log("TODO: Docking...\n");
									}

								// NOTE: If human inside vehicle, don't collide vehicle and its driver

								// TODO: Knockers and other types of blobs

								// Else do regular collision:
									else {
										collisions++;
										collide(blob_a, blob_b);
										float damageamount = 1;	// TODO
										blob_a->damage(damageamount);
										blob_b->damage(damageamount);
									}
							}
						}
					}
				}
			}
			total_collisions += collisions;
			if (collisions > max_collisions)
				max_collisions = collisions;
		}
	}
	return collisions;
}

void Gamespace::apply_blackholes() {
	for (int hole=0; hole<gameplay->level->blackholes.size(); hole++) {
		for (int blob=0; blob<blobs.size(); blob++) {
			//if (get_distance(blobs[blob]->location, gameplay->level->blackholes[hole]->location) > 10) {
				blobs[blob]->heading.i += 0.0001 * (gameplay->level->blackholes[hole]->location.x - blobs[blob]->location.x);
				blobs[blob]->heading.j += 0.0001 * (gameplay->level->blackholes[hole]->location.y - blobs[blob]->location.y);
			//} else {
				//blobs[blob]->can_expire = true;
				//blobs[blob]->expirecounter = 0;
			//}
		}
	}
}

void Gamespace::age() {
	for (uint32_t i=0; i<blobs.size(); i++) {
		blobs[i]->age();
	}
}

bool Gameblob::is_expired() {
	return (can_expire and expirecounter <= 0);
}

//void Gamespace::apply_gravity() {
	//log("Gamespace::apply_gravity");
//}

uint32_t Gamespace::dispose_expired_gameblobs() {
	// FIXME: Don't erase from vector while iterator is in use
	std::vector<Gameblob*> blobs_left;
	uint32_t amount_of_deleted = 0;
	for (uint32_t i=0; i<blobs.size(); i++) {
		if (blobs[i]->is_expired()) {
			amount_of_deleted++;
			if (blobs[i]->type != GAMEBLOB_TYPE_HUMAN and blobs[i]->type != GAMEBLOB_TYPE_VEHICLE)
				delete blobs[i];
		} else {
			blobs_left.push_back(blobs[i]);
		}
	}
	blobs.clear();	// or delete blobs ?
	blobs = blobs_left;
	return amount_of_deleted;
}

/*
// TODO: Use level blocks to alter resistance
void Gamespace::apply_airresistance() {
	for (int i=0; i<blobs.size(); i++) {
		blobs[i)->heading.i *= airresistance;
		blobs[i)->heading.j *= airresistance;
	}
}
*/
