
/**
* @file   particle.h
* @brief  パーティクル
*
* @author wem
* @date   2017.1.21
*/

#include "precompiled.h"


Particle::Particle()
  : pos_  (ofVec2f(0, 0)   )
  , size_ (ofVec2f(0, 0)   )
  , vel_  (ofVec2f(0, 0)   )
  , color_(ofColor(0, 0, 0))
  , limit_(0)
  , timer_(0)
{}

void Particle::update(float deltaTime) {
  float sync = deltaTime * ofGetFrameRate();
  timer_ += deltaTime;
  vel_.y -= 3.0f; // 重力らしき処理
  pos_   += vel_ * sync;
}

void Particle::draw() {
  ofPushStyle();
  ofSetColor(color_);
  ofDrawRectangle(pos_, size_.x, size_.y);
  ofPopStyle();
}

bool Particle::timeup() {
  if (timer_ > limit_) {
    return true;
  }
  else { return false; }
}
