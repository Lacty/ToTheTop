
/**
 * @file   brick.cpp
 * @brief  レンガ
 *
 * @author y.akira
 * @date   2016.12.29
 */

#include "precompiled.h"


Brick::Brick() {
	name_ = "Brick";
	tag_  =  BRICK ;
  
  color_ = ofColor(30, 30, 30, 255);
}

void Brick::setup() {
	enableUpdate();
	enableCollision();
}

void Brick::update(float deltaTime) {
  x_.update(deltaTime);
  y_.update(deltaTime);
  
  pos_.set(x_, y_);
}

void Brick::draw() {
	ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), round_);
}

void Brick::onCollision(Actor* c_actor) {}


void Brick::moveTo(const ofVec2f& pos, AnimCurve curve, float time) {
  x_.animateFromTo(pos_.x, pos.x);
  y_.animateFromTo(pos_.y, pos.y);
  
  x_.setDuration(time);
  y_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
}

void Brick::moveTo(float x, float y, AnimCurve curve, float time) {
  x_.animateFromTo(pos_.x, x);
  y_.animateFromTo(pos_.y, y);
  
  x_.setDuration(time);
  y_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
}

void Brick::setRectRound(float r) {
  round_ = r;
}
