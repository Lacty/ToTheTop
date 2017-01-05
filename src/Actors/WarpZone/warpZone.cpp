
#include "precompiled.h"


void WarpZone::setDistination(ofVec2f& pos) {
	destination = pos;

	x_.animateFromTo(pos_.x, pos.x);
	y_.animateFromTo(pos_.y, pos.y);

	x_.setDuration(1);
	y_.setDuration(1);

	x_.setCurve(EASE_IN);
	y_.setCurve(EASE_IN);
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
		x_.update(deltaTime);
		y_.update(deltaTime);

		c_Pactor->setPos(ofVec2f(x_, y_));
		if (destination == ofVec2f(x_, y_)) {
			destroy();
		}
	}
}

void WarpZone::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void WarpZone::onCollision(Actor* c_actor) {
	if (c_actor->getTag() == PLAYER) {
		color_ = ofFloatColor(0, 0, 0, 0);
		c_Pactor = c_actor;
		warp_ = true;
	}
}