
#include "precompiled.h"


void Brick::moveTo(ofVec2f& pos) {
	fallPoint_ = pos;
}

ofVec2f Brick::getFallPoint() {
	return fallPoint_;
}

Brick::Brick() {
	name_ = "Brick";
	tag_ = 1;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();

	fallSetup();
}

void Brick::fallSetup() {
	vel_ = ofVec2f(pos_.x, 0.0f);
	animPos_.animateFromTo(pos_.y, fallPoint_.y);
	animPos_.setDuration(1);
	AnimCurve curve = (AnimCurve)(VERY_LATE_LINEAR);
	animPos_.setCurve(curve);
}

void Brick::update(float deltaTime) {
	animPos_.update(deltaTime * 5);
	vel_.y = animPos_.val();
	pos_ = vel_;
}

void Brick::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {}
