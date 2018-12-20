#include "shield.hpp"

Shield_bounce::Shield_bounce() {
	description = "Bounce projectiles away.";
}

Shield_cold::Shield_cold() {
	description = "Protect from freezing.";
}

Shield_electro::Shield_electro() {
	description = "Protect from electro weapon and EMP.";
}

Shield_hot::Shield_hot() {
	description = "Protect from fire.";
}

Shield_inertialdamper::Shield_inertialdamper() {
	description = "Keep trajectory still at collision, recoil or when being blasted at. Doesn't work with gravity or tractor beam.";
}

Shield_lifesteal::Shield_lifesteal() {
	description = "Protect from life stealing.";
}

Shield_lightscreen::Shield_lightscreen() {
	description = "Allows to see in bright light, protects from blindness caused by flashes.";
}

Shield_mirror::Shield_mirror() {
	description = "Reflects laser away.";
}

Shield_repel::Shield_repel() {
	description = "Repel projectiles away.";
}
