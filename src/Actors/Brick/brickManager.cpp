
#include "precompiled.h"


void BrickManager::updateBricks() {
	sponeBrick();
}

void BrickManager::sponeBrick() {
	count_ += ofGetLastFrameTime();
	if (count_ >= 3) {
		setBrick();
		count_ = 0;
	}
}

void BrickManager::setBrick() {
	Brick brick;
	brick.setColor(ofColor(0, 0, 0));
	brick.setSize(ofVec2f(50, 50));
	brick.setFallSpeed(100.0f);
	brick.setPos(ofVec2f(ofRandom(brick.getSize().x, ofGetWindowWidth() - brick.getSize().x),
		-brick.getSize().y));
	brick.moveTo(ofVec2f(brick.getPos().x, ofGetWindowHeight()));
	bricks_.push_front(brick);
	AddActor(make_shared<Brick>(bricks_.front()));
}