
/**
 * @file   conspecies.cpp
 * @brief  同種
 *
 * @author y.akira
 * @date   2017.01.21
 */

#include "precompiled.h"


Conspecies::Conspecies() {
  name_ = "Conspecies";
  tag_  =  CONSPECIES;
  
  color_ = ofColor(255, 0, 0);
}

void Conspecies::setup() {
  enableUpdate();
  enableCollision();
}

void Conspecies::update(float deltaTime) {}

void Conspecies::draw() {
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), 6);
}

void Conspecies::onCollision(Actor *c_actor) {
  if (c_actor->getTag() == PLAYER) {}
  
  if (c_actor->getTag() == BRICK) {}
}
