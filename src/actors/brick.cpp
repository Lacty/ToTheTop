
#include "brick.h"


Brick::Brick() {
  size_.set(20, 20);
}

Brick::Brick(const ofVec3f& pos, const ofVec3f& size, bool active) :
active_(active) {
  pos_  = pos;
  size_ = size;
}


void Brick::setup() {}

void Brick::update(float deltaTime) {
  if (!active_) { return; }
  
  // 等速落下
  pos_.y -= deltaTime * 30.0f;
}

void Brick::draw() {
  if (active_) {
    color_ = ofColor(140, 140, 250);
  } else {
    color_ = ofColor(250, 140, 140);
  }
  
  ofSetColor(color_);
  ofDrawRectangle(pos_, size_.x, size_.y);
}

bool& Brick::active() { return active_; }
