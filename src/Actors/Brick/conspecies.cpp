
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
  tag_  = CONSPECIES;

  tex_.load("Texture/conspecies.png");
  tex_.mirror(true, false);

  splitSize_ = ofVec2f(0, 0);
  colPlayer_ = false;

  // デフォルトとプレイ時の画面サイズの比率を比較
  ofxJSON json;
  json.open("user.json");
  auto w = json["Window"]["width"].asInt();
  auto h = json["Window"]["height"].asInt();
  windowRatio_ = ofVec2f(ofGetWidth() / (float)w,
    ofGetHeight() / (float)h);
  timer_     = 0.0f;
  spawnTime_ = 0.2f;
  over_      = false;
  splitSize_ = ofVec2f(0, 0);
  colPlayer_ = false;
}

void Conspecies::setup() {
  texColor_   = ofFloatColor::white - color_;
  oneTimePos_ = pos_;
  animX_.setCurve(EASE_OUT_BACK);
  animX_.animateFromTo(0, size_.x);
  animX_.setDuration(spawnTime_);
  animY_.setCurve(EASE_OUT_BACK);
  animY_.animateFromTo(0, size_.y);
  animY_.setDuration(spawnTime_);

  enableUpdate();
}

void Conspecies::update(float deltaTime) {
  // 生成から一定時間経過するまで当たり判定を付けない
  if (timer_ >= spawnTime_) {
    if (!over_) {
      enableCollision();
      over_ = true;
    }
  }
  else {
    if (!resque_.lock()) {
      resque_ = dynamic_pointer_cast<uiResque>(FindUI(RESQUE));
      return;
    }

    // タイマーに加算しながら大きさをアニメーションで変更させる
    timer_ += deltaTime;
    animX_.update(deltaTime);
    size_.x = animX_;
    pos_.x = oneTimePos_.x + (size_.x / 20);
    animY_.update(deltaTime);
    size_.y = animY_;
    pos_.y = oneTimePos_.y + (size_.y / 20);


    // 当たり判定が有効になるまでパーティクルを生成
    for (int i = 0; i < 3; i++) {
      shared_ptr<Particle> part = make_shared<Particle>();
      auto randSize = ofRandom(2.f, 3.f);
      part->disableCollision();
      part->enableUpdate();
      part->setPos(pos_ + size_ / 2);
      part->setVel({ static_cast<float>(ofRandom(-8.f, 8.f)), static_cast<float>(ofRandom(-8.f, 8.f)), 0 });
      part->setSize({ static_cast<float>((i + 1) * randSize), static_cast<float>((i + 1) * randSize), 0 });
      part->setDestroyTime(0.1f);
      part->useGravity(false);
      part->setAnimColor(color_, color_);
      part->setSizeRatio(0.4);

      AddActor(part);
    }
  }

  // Playerとの接触判定後に縮小開始
  if (colPlayer_) {
    // 縮小しながら座標を中心に移動させる
    size_ -= splitSize_;
    pos_ += splitSize_ / 2;
  }

  // サイズが０以下になったら削除
  if (size_.x < 0 || size_.y < 0) {
    if (!isSoundPlaying(RESCUE_CSP)) {
      PlaySound(RESCUE_CSP);

      // 救出者数を加算
      if (auto resque = resque_.lock()) {
        auto rn = resque->getNum();
        rn += 1;
        resque->setNum(rn);
      }
    }
    for (auto par : particles_) {
      AddActor(par);
    }
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
    splitSize_ = size_ / 10;  // 縮小倍率

                              // パーティクルの生成
    for (int i = 0; i < 10; i++) {
      shared_ptr<HomingParticle> part = make_shared<HomingParticle>(c_actor);
      part->setPos(pos_ + size_ / 2);
      // 円形にパーティクルが散るようにゴリ押し
      if (i == 0) part->setVel({ static_cast<float>(0 * windowRatio_.x),
                                 static_cast<float>(15.0 * windowRatio_.y), 0 });
      if (i == 1) part->setVel({ static_cast<float>(6.0 * windowRatio_.x),
                                 static_cast<float>(9.0 * windowRatio_.y), 0 });
      if (i == 2) part->setVel({ static_cast<float>(12.0 * windowRatio_.x),
                                 static_cast<float>(3.0 * windowRatio_.y), 0 });
      if (i == 3) part->setVel({ static_cast<float>(12.0 * windowRatio_.x),
                                 static_cast<float>(-3.0 * windowRatio_.y), 0 });
      if (i == 4) part->setVel({ static_cast<float>(6.0 * windowRatio_.x),
                                 static_cast<float>(-9.0 * windowRatio_.y), 0 });
      if (i == 5) part->setVel({ static_cast<float>(0 * windowRatio_.x),
                                 static_cast<float>(-15.0 * windowRatio_.y), 0 });
      if (i == 6) part->setVel({ static_cast<float>(-6.0 * windowRatio_.x),
                                 static_cast<float>(-9.0 * windowRatio_.y), 0 });
      if (i == 7) part->setVel({ static_cast<float>(-12.0 * windowRatio_.x),
                                 static_cast<float>(-3.0 * windowRatio_.y), 0 });
      if (i == 8) part->setVel({ static_cast<float>(-12.0 * windowRatio_.x),
                                 static_cast<float>(3.0 * windowRatio_.y), 0 });
      if (i == 9) part->setVel({ static_cast<float>(-6.0 * windowRatio_.x),
                                 static_cast<float>(9.0 * windowRatio_.y), 0 });

      auto randSize = ofRandom(1.4f, 2.4f);
      part->setSize({ static_cast<float>(((i + 2) / 2) * randSize) * windowRatio_.x,
                      static_cast<float>(((i + 2) / 2) * randSize) * windowRatio_.y,
                      0 });
      part->setColor(color_);
      particles_.emplace_back(part);
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
      part->setPos(pos_ + size_ / 2);
      part->setVel({ static_cast<float>(ofRandom(-3.f, 3.f) * windowRatio_.x),
                     static_cast<float>(ofRandom(0.f, 10.f) * windowRatio_.y), 0 });
      part->setSize({ static_cast<float>(((i + 2) / 2) * randSize) * windowRatio_.x,
                      static_cast<float>(((i + 2) / 2) * randSize) * windowRatio_.y,
                      0 });
      part->setDestroyTime(5.f);
      part->setGravity(0.4f);
      part->useGravity(true);
      part->setAnimColor(color_, ofFloatColor::white);
      part->setSizeRatio(0.5);

      AddActor(part);
    }

    // 音を鳴らして削除
    PlaySound(CSP_CRUSH);
    destroy();
  }
}
