
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

  splitSize_ = ofVec2f(0, 0);
  colPlayer_ = false;
}

void Conspecies::setup() {
  texColor_ = ofFloatColor::white - color_;
  enableUpdate();
  enableCollision();
}

void Conspecies::update(float deltaTime) {
  // Playerとの接触判定後に縮小開始
  if (colPlayer_) {
    // 縮小しながら座標を中心に移動させる
    size_ -= splitSize_;
    pos_  += splitSize_/2;
  }

  // サイズが０以下になったら削除
  if (size_.x < 0 || size_.y < 0) {
    destroy();
  }
}

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
    colPlayer_ = true;        // updateの処理スイッチ
    splitSize_ = size_ / 15;  // 縮小倍率

    // パーティクルの生成
    for (int i = 0; i < 10; i++) {
      shared_ptr<HomingParticle> part = make_shared<HomingParticle>(c_actor);
      part->setPos(pos_ + size_/2);
      // 円形にパーティクルが散るようにゴリ押し
      if (i == 0) part->setVel({ static_cast<float>(0)    , static_cast<float>(15)  , 0 }); // 0
      if (i == 1) part->setVel({ static_cast<float>(6.0)  , static_cast<float>(9.0) , 0 }); // 1
      if (i == 2) part->setVel({ static_cast<float>(12.0) , static_cast<float>(3.0) , 0 }); // 2
      if (i == 3) part->setVel({ static_cast<float>(12.0) , static_cast<float>(-3.0), 0 }); // 3
      if (i == 4) part->setVel({ static_cast<float>(6.0)  , static_cast<float>(-9.0), 0 }); // 4
      if (i == 5) part->setVel({ static_cast<float>(0)    , static_cast<float>(-15) , 0 }); // 5
      if (i == 6) part->setVel({ static_cast<float>(-6.0) , static_cast<float>(-9.0), 0 }); // 6
      if (i == 7) part->setVel({ static_cast<float>(-12.0), static_cast<float>(-3.0), 0 }); // 7
      if (i == 8) part->setVel({ static_cast<float>(-12.0), static_cast<float>(3.0) , 0 }); // 8
      if (i == 9) part->setVel({ static_cast<float>(-6.0) , static_cast<float>(9.0) , 0 }); // 9

      auto randSize = ofRandom(1.4f, 2.4f);
      part->setSize({static_cast<float>(((i + 2) / 2) * randSize), static_cast<float>(((i + 2) / 2) * randSize), 0});
      part->setColor(color_);
  
      AddActor(part);
    }

    disableCollision();
  }
  
  // 潰された際に重力をかけたパーティクルを生成
  if (c_actor->getTag() == BRICK) {
    for (int i = 0; i < 20; i++) {
      auto randSize = ofRandom(0.7f, 1.2f);
      shared_ptr<Particle> part = make_shared<Particle>();
      part->disableCollision();
      part->enableUpdate();
      part->setPos(pos_ + size_/2);
      part->setVel({static_cast<float>(ofRandom(-3.f, 3.f)), static_cast<float>(ofRandom(0.f, 10.f)), 0});
      part->setSize({ static_cast<float>(((i + 2) / 2) * randSize), static_cast<float>(((i + 2) / 2) * randSize), 0 });
      part->setDestroyTime(5.f);
      part->setGravity(0.4f);
      part->useGravity(true);
      part->setAnimColor(color_, ofFloatColor::white);
      part->setSizeRatio(0.5);

      AddActor(part);
    }
    // 削除
    destroy();
  }
}
