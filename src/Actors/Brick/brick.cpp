
#include "precompiled.h"


void Brick::moveTo(ofVec2f& pos) {
	fallPoint_ = pos;
}

Brick::Brick() {
	name_ = "Brick";
	size_ = ofVec2f(50, 50);
	color_ = ofColor(0, 0, 0);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	vel_ = ofVec2f(0, 75.0f);
	tag_ = 1;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();

}

void Brick::update(float deltaTime) {
	vel_ = fallPoint_ - pos_;
	if (pos_.y <= fallPoint_.y) {
		pos_ += vel_*ofGetLastFrameTime();
	}
}

void Brick::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {
	if (c_actor->getTag() == 1 && pos_.y < c_actor->getPos().y) {
		pos_ -= vel_*ofGetLastFrameTime();

		count_ += ofGetLastFrameTime();
		if (count_ > 15) {
			destroy();
		}
	}
}