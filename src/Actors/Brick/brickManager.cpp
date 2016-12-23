
#include "precompiled.h"


void BrickManager::setup() {
	numX_ = 0;
	numY_ = 1;
	for (int r = 0; r < row_; r++) {
		for (int c = 0; c < column_; c++) {
			fallPoints_[c][r].x = (ofGetWindowWidth() / column_)*c;
			fallPoints_[c][r].y = ofGetWindowHeight() - (ofGetWindowHeight() / row_) * (r + 1);
			existences_[c][r] = false;
		}
	}
}

void BrickManager::update(float& deltaTime) {
	count_ += deltaTime;
	if (count_ >= 1 && count_ <= 1.1) {
		spone();
	}

	a += deltaTime;

	if (a > 5) {
		bricks_.begin()->moveTo(ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight()));
	}
}

void BrickManager::spone() {
	setBrick();
	numX_++;
	if (numX_ >= column_) {
		numY_++;
		numX_ = 0;
	}
}

void BrickManager::setBrick() {
	Brick brick;
	brick.setColor(ofColor(0, 0, 0));
	brick.setSize(ofVec2f(ofGetWindowWidth() / column_, ofGetWindowHeight() / row_));
	brick.setPos(ofVec2f(fallPoints_[numX_][numY_].x, -brick.getSize().y));
	brick.moveTo(ofVec2f(fallPoints_[numX_][numY_].x, fallPoints_[numX_][numY_].y));
	bricks_.push_front(brick);
	existences_[numX_][numY_] = true;
	AddActor(make_shared<Brick>(bricks_.front()));
}