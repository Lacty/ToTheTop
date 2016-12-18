
#include "precompiled.h"


Brick::Brick() {
  // 名前とサイズを設定
  name_ = "Brick";
  pos_ = ofVec2f(0, 0);
  size_ = ofVec2f(30, 30);
}

void Brick::setup() {
  // 画像のロード
  brickImg_.load("textures/brick.jpg");

  enableUpdate();
  enableCollision();
}

void Brick::update(float deltaTime) {}

void Brick::draw() {
  ofSetColor(ofColor::white);
  brickImg_.draw(pos_);
}

void Brick::onCollision(Actor* c_actor) {}
