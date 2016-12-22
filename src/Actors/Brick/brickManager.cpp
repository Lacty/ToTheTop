
#include "precompiled.h"


void BrickManager::sponeBrick() {
	count_ += ofGetLastFrameTime();
	if (count_ >= 3 && num_ <= 2) {
		setBrick();
		count_ = 0;
		num_++;
	}
}

void BrickManager::setBrick() {
	Brick brick;
	brick.setPos(ofVec2f(0, 0));
	brick.setMoveTo(ofVec2f(num_*20, ofGetWindowHeight()-100));
	bricks_.push_front(brick);
	AddActor(make_shared<Brick>(bricks_.front()));
}