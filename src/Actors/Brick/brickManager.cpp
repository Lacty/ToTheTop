
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
	brick.setPos(ofVec2f(ofGetWindowWidth() / 2, 0));
	brick.moveTo(ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() - 100));
	bricks_.push_front(brick);
	AddActor(make_shared<Brick>(bricks_.front()));
}