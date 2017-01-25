
/**
 * @file   particleSystem.cpp
 *
 * @author y.akira
 * @date   2017.01.24
 */

#include "precompiled.h"


// =================================================
// パーティクルシステム
ParticleSystem::ParticleSystem()
 : play_           ( false )
 , deltaTime_      ( 0 )
 , destroyTime_    ( 0 )
 , createDelta_    ( 0 )
 , createInterval_ ( 1 )
 , partDestroyTime_( 3 )
 , startCol_       ( 1 )
 , endCol_         ( 1 )
 , sizeRatio_      ( 1 )
 , gravity_        ( 0 )
 , addGravity_     ( false )
{}

ParticleSystem::ParticleSystem(bool activate, float sizeRatio, float destroyTime, bool addGravity)
 : play_           ( activate    )
 , deltaTime_      ( 0 )
 , destroyTime_    ( destroyTime )
 , createDelta_    ( 0 )
 , createInterval_ ( 1 )
 , partDestroyTime_( 3 )
 , startCol_       ( 1 )
 , endCol_         ( 1 )
 , sizeRatio_      ( sizeRatio )
 , gravity_        ( 0.2f )
 , addGravity_     ( addGravity )
{}

ParticleSystem::ParticleSystem(bool activate, ofColor startColor, ofColor endColor, float sizeRatio, float destroyTime, bool addGravity)
  : play_           ( activate )
  , deltaTime_      ( 0 )
  , destroyTime_    ( destroyTime )
  , createDelta_    ( 0 )
  , createInterval_ ( 1 )
  , partDestroyTime_( 3 )
  , startCol_       ( startColor )
  , endCol_         ( endColor )
  , sizeRatio_      ( sizeRatio )
  , gravity_        ( 0.2f )
  , addGravity_     ( addGravity )
{}

void ParticleSystem::setup() {
  enableUpdate();
}

void ParticleSystem::update(float deltaTime) {
  // 実行中、時間を進める
  if (play_) {
    deltaTime_ += deltaTime;
  }
  
  // 自滅する時間になったら
  if (hasDestroyTime()) {
    bool timeIsNow = deltaTime_ > destroyTime_;
    if (timeIsNow) {
      // 生成を止める
      stop();
      
      // ぱーてくるが全部消えたら
      if (!particles_.size()) {
      
        // ActorManagerから消える
        destroy();
      }
    }
  }
  
  updateParts(deltaTime);
}

void ParticleSystem::draw() {
  for (auto& part : particles_) {
    part->draw();
  }
}

void ParticleSystem::gui() {
  if (ImGui::BeginMenu("ParticleSystem")) {
    ImGui::Text("%s", ofToString(particles_.size()).c_str());
    if (ImGui::Checkbox("Play", &play_)) {
      play_? play() : stop();
    }

    if (ImGui::Checkbox("AddGravity", &addGravity_)) {
      addGravity_ ? addGravity_ = true : addGravity_ = false;
    }

    ImGui::InputFloat2("Posision", pos_.getPtr());
    ImGui::InputFloat2("Range", size_.getPtr());
    ImGui::InputFloat("SystemDestroyTime", &destroyTime_);
    ImGui::InputFloat("Interval", &createInterval_);
    ImGui::InputFloat("ParticleDestroyTime", &partDestroyTime_);
    ImGui::InputFloat2("SizeMin", sizeMin_.getPtr());
    ImGui::InputFloat2("SizeMax", sizeMax_.getPtr());
    ImGui::InputFloat2("VelMin", velocityMin_.getPtr());
    ImGui::InputFloat2("VelMax", velocityMax_.getPtr());
    ImGui::ColorEdit3("StartColor", &startCol_.r);
    ImGui::ColorEdit3("EndColor", &endCol_.r);
    ImGui::InputFloat("SizeRatio", &sizeRatio_);
    ImGui::InputFloat("Gravity", &gravity_);
    ImGui::EndMenu();
  }
}


void ParticleSystem::updateParts(float delta) {
  createDelta_ += delta;

  // 各パーティクル更新
  for (auto& part : particles_) {
    part->update(delta);
  }
  
  // パーティクルの追加処理
  bool shouldCreate = createDelta_ > createInterval_;
  if ( play_ && shouldCreate ) {
    createDelta_ -= createInterval_;
    create();
  }
  
  // 削除対象を消す
  particles_.remove_if(
    [] (const pParticle_t& part)->bool {
      return part->shouldDestroy();
    }
  );
}

void ParticleSystem::create() {
  float x = 0, y = 0, z = 0;
  
  x = ofRandom(getRectangle().x, getRectangle().width);
  y = ofRandom(getRectangle().x, getRectangle().height);
  ofVec3f pos(x, y, z);
  
  x = ofRandom(velocityMin_.x, velocityMax_.x);
  y = ofRandom(velocityMin_.y, velocityMax_.y);
  ofVec3f velocity(x, y, z);
  
  x = ofRandom(sizeMin_.x, sizeMax_.x);
  y = ofRandom(sizeMin_.y, sizeMax_.y);
  ofVec3f size(x, y, z);

  pParticle_t part = make_unique<Particle>();
  part->setPos(move(pos));
  part->setVel(move(velocity));
  part->setSize(move(size));
  part->setDestroyTime(partDestroyTime_);
  part->setAnimColor(startCol_, endCol_);
  part->setSizeRatio(sizeRatio_);
  part->setGravity(gravity_);
  part->addGravity(addGravity_);

  particles_.emplace_back(move(part));
}

void ParticleSystem::play() {
  play_        = true;
  deltaTime_   = 0;
  createDelta_ = 0;
}

void ParticleSystem::stop() {
  play_ = false;
}

void ParticleSystem::killAll() {
  play_ = false;
  
  // 全削除
  for (auto& p : particles_) {
    p->destroy();
  }
}

bool ParticleSystem::hasDestroyTime()    const { return bool(destroyTime_); }

float ParticleSystem::getInterval()      const { return createInterval_; }
ofVec2f ParticleSystem::getSizeMin()     const { return sizeMin_; }
ofVec2f ParticleSystem::getSizeMax()     const { return sizeMax_; }
ofVec2f ParticleSystem::getVelocityMin() const { return velocityMin_; }
ofVec2f ParticleSystem::getVelocityMax() const { return velocityMax_; }

void ParticleSystem::setSysDestroyTime(float time)  { destroyTime_ = time; }
void ParticleSystem::setPartDestroyTime(float time) { partDestroyTime_ = time; }

void ParticleSystem::setCreateSize(ofVec2f min, ofVec2f max) {
  sizeMin_ = min;
  sizeMax_ = max;
}

void ParticleSystem::setCreateVelocity(ofVec2f min, ofVec2f max) {
  velocityMin_ = min;
  velocityMax_ = max;
}

void ParticleSystem::setAnimColor(ofFloatColor start, ofFloatColor end) {
  startCol_ = start;
  endCol_   = end;
}

// =================================================
// パーティクル
Particle::Particle()
 : deltaTime_  ( 0 )
 , destroyTime_( 60 )
 , sizeRatio_  (1.0f)
 , gravity_    (0.2f)
{}


void Particle::setup() {}

void Particle::update(float deltaTime) {
  deltaTime_ += deltaTime;

  // 重力を掛ける処理
  if (addGravity_) { vel_.y -= gravity_; }

  // 設定された加速度で移動する
  pos_ += vel_;

  // 時間経過で色を変化させる(startとendの色が違えば)
  r_.update(deltaTime / destroyTime_);
  g_.update(deltaTime / destroyTime_);
  b_.update(deltaTime / destroyTime_);
  color_ = ofFloatColor(r_, g_, b_);
  
  // 時間の経過でサイズを変更する
  if (sizeRatio_ != 1.0f) {
    ofVec2f ns = size_*sizeRatio_*deltaTime;
    size_ += ns;
  }

  // 自滅時間になったら死ぬ
  if (deltaTime_ > destroyTime_ ||
      size_.x <= 0 || size_.y <= 0) {
    destroy();
  }
}

void Particle::draw() {
  ofSetColor(color_);
  ofDrawCircle(pos_, size_.x);
}

void Particle::setDestroyTime(float time) {
  destroyTime_ = max(0.0f, time);
}

void Particle::setAnimColor(ofFloatColor start, ofFloatColor end) {
  startCol_ = start;
  endCol_   = end;

  r_.setDuration(1);
  r_.setRepeatType(PLAY_ONCE);
  r_.setCurve(LINEAR);
  r_.animateFromTo(startCol_.r, endCol_.r);

  g_.setDuration(1);
  g_.setRepeatType(PLAY_ONCE);
  g_.setCurve(LINEAR);
  g_.animateFromTo(startCol_.g, endCol_.g);

  b_.setDuration(1);
  b_.setRepeatType(PLAY_ONCE);
  b_.setCurve(LINEAR);
  b_.animateFromTo(startCol_.b, endCol_.b);
}

void Particle::setSizeRatio(float ratio) {
  sizeRatio_ = ratio;
}

void Particle::setGravity(float gravity) {
  gravity_ = gravity;
}

void Particle::addGravity(bool g) {
  addGravity_ = g;
}
