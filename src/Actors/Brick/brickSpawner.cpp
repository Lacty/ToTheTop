
/**
 * @file   brickSpawner.cpp
 * @brief  レンガ生成機
 *
 * @author y.akira
 * @date   2016.12.30
 */

#include "precompiled.h"


BrickSpawner::BrickSpawner() {
  name_  = "BrickSpawner";
  tag_   =  BRICK_SPAWNER;
  actor_ = make_shared<Brick>();
  
  color_ = ofColor(40, 40, 40, 255);
}

void BrickSpawner::draw() {
  ofSetColor(ofColor(200, 0, 0, 50));
  ofDrawRectRounded(getRectangle(), 4);
}

void BrickSpawner::set(AnimCurve curve, float time) {
  auto brick = dynamic_cast<Brick*>(actor_.get());
  ofVec2f offset(0, ofGetWindowHeight());
  
  brick->setPos(pos_ + offset);
  brick->setSize(size_);
  brick->setColor(color_);
  brick->moveTo(pos_, curve, time);
}
