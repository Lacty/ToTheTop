
/**
* @file   brickManager.h
* @brief  レンガマネージャー
*
* @author ninja
* @date   2016.12.27
*/

#include "precompiled.h"


void BrickManager::setup() {
	count_ = 0;

	row_ = 10;
	column_ = 5;
	numX_ = 0;
	numY_ = 0;

	//落下先を事前に設定
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
		fallTerms_ = ofRandom(0, 10);
	}
	if (count_ >= 1) {
		if (fallTerms_ < 7) {
			numX_ = ofRandom(0, column_);
			for (numY_ = 0; numY_ < row_;) {
				if (existances_[numX_][numY_]) {
					numY_++;
					continue;
				}
				else {
					sponeBrick(fallPoints_[numX_][numY_]);
					existances_[numX_][numY_] = true;
					break;
				}
			}
		}
		else {
			setMinPoint();
			sponeBrick(fallPoints_[minFallPoint_[0]][minFallPoint_[1]]);
			existances_[minFallPoint_[0]][minFallPoint_[1]] = true;
		}
		count_ = 0;
	}
}

void BrickManager::setMinPoint() {
	for (int r = 0; r < row_; r++) {
		for (int c = 0; c < column_; c++) {
			if (!existances_[c][r]) {
				minFallPoint_[0] = c;
				minFallPoint_[1] = r;
				break;
			}
		}
		if (!existances_[minFallPoint_[0]][r])break;
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
	bricks_.push_front(brick);
	AddActor(bricks_.front());
}