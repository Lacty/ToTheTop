
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

  tex_.load("Texture/conspecies.png");
  tex_.mirror(true, false);
}

void Conspecies::setup() {
  texColor_ = ofFloatColor::white - color_;
  enableUpdate();
  enableCollision();
}

void Conspecies::update(float deltaTime) {}

void Conspecies::draw() {
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), 6);

  ofPushStyle();
  ofSetColor(texColor_);
  tex_.draw(pos_.x, pos_.y, size_.x, size_.y);
  ofPopStyle();
}

void Conspecies::onCollision(Actor *c_actor) {
  if (c_actor->getTag() == PLAYER) {

    // パーティクルの生成
    for (int i = 0; i < 10; i++) {
      shared_ptr<HomingParticle> part = make_shared<HomingParticle>(c_actor);
      part->setPos(pos_ + size_);
      //part->setVel({static_cast<float>(5 - i), static_cast<float>(5 - i), 0});
      // 円形にパーティクルが散るようにゴリ押し
      if (i == 0) part->setVel({ static_cast<float>(0)   , static_cast<float>(15)   , 0 }); // 0
      if (i == 1) part->setVel({ static_cast<float>(6.0) , static_cast<float>(9.0) , 0 }); // 1
      if (i == 2) part->setVel({ static_cast<float>(12.0) , static_cast<float>(3.0) , 0 }); // 2
      if (i == 3) part->setVel({ static_cast<float>(12.0) , static_cast<float>(-3.0), 0 }); // 3
      if (i == 4) part->setVel({ static_cast<float>(6.0) , static_cast<float>(-9.0), 0 }); // 4
      if (i == 5) part->setVel({ static_cast<float>(0)   , static_cast<float>(-15)  , 0 }); // 5
      if (i == 6) part->setVel({ static_cast<float>(-6.0), static_cast<float>(-9.0), 0 }); // 6
      if (i == 7) part->setVel({ static_cast<float>(-12.0), static_cast<float>(-3.0), 0 }); // 7
      if (i == 8) part->setVel({ static_cast<float>(-12.0), static_cast<float>(3.0) , 0 }); // 8
      if (i == 9) part->setVel({ static_cast<float>(-6.0), static_cast<float>(9.0) , 0 }); // 9

      auto randSize = ofRandom(0.8f, 1.5f);
      part->setSize({static_cast<float>(i * randSize), static_cast<float>(i * randSize), 0});
      part->setColor(color_);
  
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
