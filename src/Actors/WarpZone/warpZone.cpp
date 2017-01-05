
#include "precompiled.h"


void WarpZone::setDistination(ofVec2f& pos) {
	destination = pos;
}

void WarpZone::setDistination(float posX, float posY) {
	ofVec2f pos = ofVec2f(posX, posY);
	destination = pos;
}

void WarpZone::setup() {
	name_ = "WarpZone";
	color_ = ofFloatColor(155, 0, 0);
	warp_ = false;

	enableCollision();
	enableUpdate();
}

void WarpZone::update(float deltaTime) {
	if (warp_) {
		warp(p_actor, deltaTime);
	}
}

void WarpZone::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void WarpZone::onCollision(Actor* c_actor) {
	if (c_actor->getName() == "Player") {
		color_ = ofFloatColor(0, 0, 0, 0);
		p_actor = dynamic_cast<Player*>(c_actor);
		warp_ = true;
	}
}

void WarpZone::warp(Player* player, float deltaTime) {
	ofVec2f c_pPos = player->getPos();
	ofVec2f velocity = (destination - c_pPos) * deltaTime;
	player->setVel(ofVec2f(velocity.x, velocity.y + player->getGravity()));
	if (velocity.y <= 0) {
		warp_ = false;
		destroy();
	}
}