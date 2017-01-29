
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
    
    // パーティクルの生成
    for (int i = 0; i < 10; i++) {
      shared_ptr<HomingParticle> part = make_shared<HomingParticle>(c_actor);
      part->setPos(pos_ + size_);
      part->setVel({static_cast<float>(5 - i), static_cast<float>(5 - i), 0});
      part->setSize({static_cast<float>(i * 0.5f), static_cast<float>(i * 0.5f), 0});
  
      AddActor(part);
    }
    // 削除
    destroy();
  }
  
  if (c_actor->getTag() == BRICK) {
    // とりあえず削除
    destroy();
  }
}
