
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
  if (c_actor->getTag() == PLAYER) {
    // とりあえず削除
    destroy();
  }
  
  if (c_actor->getTag() == BRICK) {
    // とりあえず削除
    destroy();
  }
}
