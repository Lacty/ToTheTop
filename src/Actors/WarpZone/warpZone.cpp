﻿
#include "precompiled.h"


void WarpZone::setDistination(const ofVec2f& pos) {
	destPos_ = pos;

	x_.animateFromTo(pos_.x, destPos_.x);
	y_.animateFromTo(pos_.y, destPos_.y);

	x_.setDuration(1);
	y_.setDuration(1);

	x_.setCurve(EASE_IN);
	y_.setCurve(EASE_IN);
}

WarpZone::WarpZone() {
	name_ = "WarpZone";
	tag_ = WARPZONE;
	color_ = ofColor(255, 255, 255, 255);
	size_ = ofVec2f(100, 100);

	tex_.load("Texture/warphole.png");
	tex_.mirror(true, false);
	player_ = nullptr;
	warp_ = false;
	degree_ = 0;

	holeValue_ = 5;
	holeScale_ = ofVec2f(100, 70);
}

void WarpZone::setup() {
	enableCollision();
	enableUpdate();
}

void WarpZone::update(float deltaTime) {
	if (!wp_brickMgr_.lock()) {
		wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
		return;
	}

	degree_ -= deltaTime * 10;

	if (!player_&&!warp_) { return; }
	x_.update(deltaTime);
	y_.update(deltaTime);

	player_->setPos(ofVec2f(x_, y_));
	if (destPos_ == ofVec2f(x_, y_)) {
		if (auto brickMgr = wp_brickMgr_.lock()) {
			brickMgr->enableUpdate();
		}
		player_->enableCollision();
		player_->canControl(true);
		player_->addVelocity(true);
		destroy();
	}
}

void WarpZone::draw() {
	ofSetColor(color_);

	//ワープ開始地点の画像
	ofPushMatrix();
	ofTranslate(ofPoint(pos_.x + size_.x / 2, pos_.y + size_.y / 2));
	ofRotate(degree_);
	tex_.draw(ofPoint(-size_.x / 2, -size_.y / 2), size_.x, size_.y);
	ofPopMatrix();

	if (!warp_) { return; }
	//ワープ終了地点の画像
	ofPushMatrix();
	ofTranslate(ofPoint(destPos_.x + size_.x / 2, destPos_.y + size_.y / 2));
	ofRotate(degree_);
	tex_.draw(ofPoint(-size_.x / 2, -size_.y / 2), size_.x, size_.y);
	ofPopMatrix();

	for (int i = 0; i < holeValue_; i++) {
		drawHole(holePos_[i]);
	}
}

void WarpZone::drawHole(ofVec2f& pos) {
	ofPushStyle();
	ofPushMatrix();
	ofNoFill();
	ofTranslate(pos);
	//プレイヤーが通り過ぎたら大きくする
	if (pos.y <= player_->getPos().y) {
		float destPosY = player_->getPos().y - pos.y;
		ofScale(destPosY / 100, 1);
	}
	ofDrawEllipse(ofVec2f(0, 0), holeScale_.x, holeScale_.y);
	ofPopMatrix();
	ofPopStyle();
}

void WarpZone::onCollision(Actor* c_actor) {
	if (player_) { return; }
	if (c_actor->getTag() == PLAYER) {
		if (auto brickMgr = wp_brickMgr_.lock()) {
			brickMgr->disableUpdate();
		}
		player_ = dynamic_cast<Player*>(c_actor);
		player_->canControl(false);
		player_->addVelocity(false);
		player_->disableCollision();
		warp_ = true;

		for (int i = 0; i < holeValue_; i++) {
			holePos_.push_back(ofVec2f(pos_ + ((destPos_ - pos_) / holeValue_) * (i + 1)));
		}
	}
}