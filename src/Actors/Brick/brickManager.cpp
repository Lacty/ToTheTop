
#include "precompiled.h"


void BrickManager::setup() {
	count_ = 0;

	row_ = 10;
	column_ = 5;
	numX_ = 0;
	numY_ = 0;

	//落下地点を設定
	for (int r = 0; r < row_; r++) {
		for (int c = 0; c < column_; c++) {
			fallPoints_[c][r].x = (ofGetWindowWidth() / column_)*c;
			fallPoints_[c][r].y = ofGetWindowHeight() - (ofGetWindowHeight() / row_) * (r + 1);
		}
	}
}

void BrickManager::update(float deltaTime) {
	UpdateActors(deltaTime);

	if (numY_ < row_) {
		count_ += deltaTime;
		numX_ = ofRandom(0, column_);
	}
	if (count_ >= 1) {
		
		for (numY_ = 0; numY_ < row_;) {
			if (existances_[numX_][numY_]) {
				numY_++;
				continue;
			}
			else {
				sponeBrick(fallPoints_[numX_][numY_]);
				break;
			}
		}

		count_ = 0;
	}
}

void BrickManager::draw() {
	DrawActors();
}

void BrickManager::sponeBrick(ofVec2f& pos) {
	shared_ptr<Brick> brick;
	brick = make_shared<Brick>();
	brick->setColor(ofColor::black);
	brick->setSize(ofVec2f(ofGetWindowWidth() / column_, ofGetWindowHeight() / row_));
	brick->setPos(ofVec2f(pos.x, -brick->getSize().y));
	brick->moveTo(pos);
	existances_[numX_][numY_] = true;
	bricks_.push_front(brick);
	AddActor(bricks_.front());
}