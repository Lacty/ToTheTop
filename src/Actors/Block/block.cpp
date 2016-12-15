
#include "precompiled.h"


Block::Block() {
	name_ = "Block";
	size_ = ofVec2f(100, 30);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	vel_ = ofVec3f(0, 50.0f);
	tag_ = 1;
}

void Block::setup() {
	enableUpdate();
	enableCollision();
}

void Block::update(float deltaTime) {
	pos_.y += vel_.y * deltaTime;
}

void Block::draw() {
	ofSetColor(ofColor(255, 0, 0));
	ofDrawRectangle(getRectangle());
}

void Block::onCollisionEnter(Actor& c_actor) {
	if (c_actor.getTag() == 1) {
		c_actor.setVel(ofVec2f(0, 0));
	}
}