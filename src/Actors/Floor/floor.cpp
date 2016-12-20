
#include "precompiled.h"


Floor::Floor() {
	name_ = "Floor";
	size_ = ofVec2f(ofGetWindowWidth(), 10);
	pos_ = ofVec2f(0, ofGetWindowHeight() - 50);
	tag_ = 1;
}

void Floor::setup() {
	enableCollision();
}

void Floor::draw() {
	ofSetColor(ofColor(0, 255, 0));
	ofDrawRectangle(getRectangle());
}

void Floor::onCollision(Actor* c_actor) {}