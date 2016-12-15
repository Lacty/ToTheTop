
#include "precompiled.h"


Barricade::Barricade() {
	name_ = "Barricade";
	size_ = ofVec2f(200, 10);
	pos_ = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() - 50);
}

void Barricade::setup() {
	enableCollision();
}

void Barricade::draw() {
	ofSetColor(ofColor(0, 255, 0));
	ofDrawRectangle(getRectangle());
}

void Barricade::onCollisionEnter(Actor& c_actor) {}