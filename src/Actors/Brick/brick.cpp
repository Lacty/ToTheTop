
#include "precompiled.h"


void Brick::moveTo(ofVec2f& pos) {
	fallPoint_ = pos;
}

Brick::Brick() {
	name_ = "Brick";
	size_ = ofVec2f(50, 50);
	color_ = ofColor(0, 0, 0);
	pos_ = ofVec3f(ofGetWindowWidth() / 2, -size_.y);
	vel_ = ofVec2f(pos_.x, 75.0f);
	tag_ = 1;
}

void Brick::setup() {
	enableUpdate();
	enableCollision();

	fallSetup();
}

void Brick::fallSetup() {
	animPos_[0].animateFromTo(pos_.x, fallPoint_.x);
	animPos_[1].animateFromTo(pos_.y, fallPoint_.y);
	animPos_[0].setDuration(1);
	animPos_[1].setDuration(1);
	AnimCurve curve = (AnimCurve)(VERY_LATE_LINEAR);
	animPos_[0].setCurve(curve);
	animPos_[1].setCurve(curve);
}

void Brick::update(float deltaTime) {
	animPos_[0].update(ofGetLastFrameTime() * 10);
	animPos_[1].update(ofGetLastFrameTime() * 10);
	vel_.x = animPos_[0].val();
	vel_.y = animPos_[1].val();
	pos_ = vel_;


}

void Brick::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {
	if (c_actor->getTag() == 1) {
		fallPoint_ = pos_;
	}
}