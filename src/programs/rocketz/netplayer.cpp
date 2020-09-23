#include "netplayer.hpp"

ClientPlayer::ClientPlayer(Gameplay* gameplay) : Player(gameplay) {
}

ClientPlayer::~ClientPlayer() {
}

ServerPlayer::ServerPlayer(Gameplay* gameplay) : Player(gameplay) {
}

ServerPlayer::~ServerPlayer() {
}

void ServerPlayer::execute() {
}
