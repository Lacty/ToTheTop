
#include "precompiled.h"


Brick::Brick() {
	name_ = "Brick";
	size_ = ofVec2f(50, 50);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	defaultVel_ = ofVec2f(0, 75.0f);
	vel_ = defaultVel_;
	tag_ = 1;

	fallPoint_ = ofVec2f(pos_.x, ofGetWindowHeight());

	yMargin_ = 0;
	hightCol_ = 60;

	count_ = 0;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();

	animPos_.animateFromTo(pos_.y, pos_.y + fallPoint_.y);
	animPos_.setDuration(2);
	AnimCurve curve = (AnimCurve)(VERY_LATE_LINEAR);
	animPos_.setCurve(curve);
}

void Brick::update(float deltaTime) {
	animPos_.update(ofGetLastFrameTime());
	vel_.y = animPos_.val();
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
		ofVec2f currentPos = c_actor->getPos() - pos_;

	}
}