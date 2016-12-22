
#include "precompiled.h"


void Brick::setMoveTo(ofVec2f& pos) {
	fallPoint_ = pos;
}

Brick::Brick() {
	name_ = "Brick";
	size_ = ofVec2f(50, 50);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	vel_ = ofVec2f(pos_.x, 75.0f);
	tag_ = 1;

	count_ = 0;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();

	fallSetup();
}

void Brick::fallSetup() {
	animPosX_.animateFromTo(pos_.x, fallPoint_.x);
	animPosY_.animateFromTo(pos_.y, fallPoint_.y);
	animPosX_.setDuration(2);
	animPosY_.setDuration(2);
	AnimCurve curve = (AnimCurve)(VERY_LATE_LINEAR);
	animPosX_.setCurve(curve);
	animPosY_.setCurve(curve);
}

void Brick::update(float deltaTime) {
	animPosX_.update(ofGetLastFrameTime());
	animPosY_.update(ofGetLastFrameTime());
	vel_.x = animPosX_.val();
	vel_.y = animPosY_.val();
	pos_ = vel_;

	count_ += ofGetLastFrameTime();
	if (count_ >= 10) {
		destroy();
	}
}

void Brick::draw() {
	ofSetColor(ofColor(0, 0, 0));
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {
	if (c_actor->getTag() == 1 && !c_actor->isDead()) {
		disableUpdate();
	}
}