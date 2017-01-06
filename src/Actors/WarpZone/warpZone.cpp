
#include "precompiled.h"


void WarpZone::setDistination(const ofVec2f& pos) {
	destPos_ = pos;

	x_.animateFromTo(pos_.x, destPos_.x);
	y_.animateFromTo(pos_.y, destPos_.y);

	x_.setDuration(1);
	y_.setDuration(1);

	x_.setCurve(EASE_IN);
	y_.setCurve(EASE_IN);
}

WarpZone::WarpZone() {
	name_ = "WarpZone";
	tag_ = WARPZONE;
	color_ = ofFloatColor(1, 0, 0);
	size_ = ofVec2f(40, 40);

	player_ = nullptr;
}

void WarpZone::setup() {
	enableCollision();
}

void WarpZone::update(float deltaTime) {
	if (!player_) { return; }
	x_.update(deltaTime);
	y_.update(deltaTime);

	player_->setPos(ofVec2f(x_, y_));
	if (destPos_ == ofVec2f(x_, y_)) {
		destroy();
	}
}

void WarpZone::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void WarpZone::onCollision(Actor* c_actor) {
	if (player_) { return; }
	if (c_actor->getTag() == PLAYER) {
		color_ = ofFloatColor(0, 0, 0, 0);
		player_ = dynamic_cast<Player*>(c_actor);
		enableUpdate();
	}
}