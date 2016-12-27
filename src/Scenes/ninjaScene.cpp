
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void NinjaScene::setup() {
	count_ = 0;
}

void NinjaScene::update(float deltaTime) {
	UpdateActors(deltaTime);

	count_ += deltaTime;
	if (count_ >= 1) {
		sponeBrick(ofVec2f(100, 500));
		count_ = 0;
	}
}

void NinjaScene::draw() {
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Ninja Scene", 20, 20);

	DrawActors();
}

void NinjaScene::sponeBrick(ofVec2f& pos) {
	shared_ptr<Brick> brick;
	brick = make_shared<Brick>();
	brick->setColor(ofColor::black);
	brick->setSize(ofVec2f(50, 50));
	brick->setPos(ofVec2f(100, 100));
	brick->moveTo(pos);
	bricks_.push_front(brick);
	AddActor(bricks_.front());
}