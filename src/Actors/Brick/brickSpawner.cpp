
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
  
  color_ = ofColor(200, 0, 0, 60);
}

void BrickSpawner::draw() {
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), 4);
}

void BrickSpawner::set(const ofVec2f& start, AnimCurve curve, float fallTime) {
  auto brick = dynamic_cast<Brick*>(actor_.get());
  
  brick->setPos(start);
  brick->setSize(size_);
  brick->moveTo(pos_, curve, fallTime);
}
