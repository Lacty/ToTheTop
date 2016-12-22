
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

	//startPos_ = pos_;
}

void Brick::update(float deltaTime) {
	vel_ = (fallPoint_ - pos_) / 0.1f;
	pos_.y += vel_.y*ofGetLastFrameTime();

	//count_ += ofGetLastFrameTime();
	//if (count_ > 20) {
	//	destroy();
	//}
}

void Brick::draw() {
	ofSetColor(color_);
	ofDrawRectangle(getRectangle());
}

void Brick::onCollision(Actor* c_actor) {
	if (c_actor->getTag() == 1 && pos_.y <= c_actor->getPos().y) {
		pos_.y -= (vel_.y*ofGetLastFrameTime()) / 2;
	}
}

//float Brick::expo_in(float time, float& startValue, float& currentValue) {
//	return currentValue * pow(2, 10 * (time / 1 - 1)) + startValue;
//}