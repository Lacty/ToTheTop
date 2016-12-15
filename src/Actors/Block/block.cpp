
#include "precompiled.h"


Block::Block() {
	name_ = "Block";
	size_ = ofVec2f(100, 30);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	vel_ = ofVec3f(0, 50.0f);

	virtualPos_ = pos_;
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
	if (c_actor.getName()=="Barricade") {
		isDead_ = true;
	}
}