
#include "precompiled.h"


void Brick::moveTo(ofVec2f& pos) {
	fallPoint_ = pos;
}

Brick::Brick() {
	name_ = "Brick";
	tag_ = 1;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();
}

void Brick::update(float deltaTime) {
	vel_ = (fallPoint_ - pos_) / 10;
	pos_ += vel_;
}

void Brick::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {}