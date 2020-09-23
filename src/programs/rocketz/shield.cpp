#include "shield.hpp"

void Shield::activate() {
	if (condition > 0)
		activated = true;
}

void Shield::deactivate() {
	if (!always_on)
		activated = false;
}

Shield_bouncer::Shield_bouncer() {
	name = "Bouncer";
	description = "Bounce projectiles away.";
}

Shield_knocker::Shield_knocker() {
	name = "Knocker";
	description = "Knock blobs away.";
}

Shield_warmer::Shield_warmer() {
	name = "Warmer";
	description = "Protect from freezing.";
}

Shield_faraday::Shield_faraday() {
	name = "Faraday";
	description = "Protect from electro weapon and EMP.";
}

Shield_cooler::Shield_cooler() {
	name = "Cooler";
	description = "Protect from heat.";
}

Shield_inertialdamper::Shield_inertialdamper() {
	name = "Inertial damper";
	description = "Retain heading and speed at collision, weapon recoil or when being blasted at.";
}

Shield_unpenetrable::Shield_unpenetrable() {
	name = "Unpenetrable shield";
	description = "Disables 100% of all damage to vehicle and human.";
}

Shield_sunscreen::Shield_sunscreen() {
	name = "Sunscreen glasses";
	description = "Allows to see in bright light, protects from blindness caused by flashes.";
}

Shield_mirror::Shield_mirror() {
	name = "Mirror";
	description = "Reflects laser away.";
}

Shield_repeller::Shield_repeller() {
	name = "Repeller";
	description = "Repel blobs.";
}
