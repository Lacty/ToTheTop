
/**
 * @file   particleSystem.cpp
 *
 * @author y.akira
 * @date   2017.01.24
 */

#include "precompiled.h"
#include <algorithm>

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
 , useGravity_     ( false )
{}

ParticleSystem::ParticleSystem(bool activate, float sizeRatio, float destroyTime, bool useGravity)
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
 , useGravity_     ( useGravity )
{}

ParticleSystem::ParticleSystem(bool activate, ofColor startColor, ofColor endColor, float sizeRatio, float destroyTime, bool useGravity)
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
  , useGravity_     ( useGravity )
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
    const bool timeIsNow = deltaTime_ > destroyTime_;
    if (timeIsNow) {
      // 生成を止める
      stop();
      
      // ぱーてくるが全部消えたら
      if (particles_.empty()) {
      
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

    if (ImGui::Checkbox("UseGravity", &useGravity_)) {
      useGravity_ ? useGravity_ = true : useGravity_ = false;
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
  particles_.erase(
    std::remove_if(particles_.begin(), particles_.end(), [] (const pParticle_t& part)->bool {
      return part->shouldDestroy();
    }),
    particles_.end()
  );
}

void ParticleSystem::create() {
  pParticle_t part = make_unique<Particle>();
  part->setPos(ofVec3f(
    ofRandom(getRectangle().x, getRectangle().width),// x
    ofRandom(getRectangle().x, getRectangle().height),// y
    0// z
  ));

  part->setVel(ofVec3f(
    ofRandom(velocityMin_.x, velocityMax_.x),// x
    ofRandom(velocityMin_.y, velocityMax_.y),// y
    0// z
  ));

  part->setSize(ofVec3f(
    ofRandom(sizeMin_.x, sizeMax_.x),// x
    ofRandom(sizeMin_.y, sizeMax_.y),// y
    0// z
  ));

  part->setDestroyTime(partDestroyTime_);
  part->setAnimColor(startCol_, endCol_);
  part->setSizeRatio(sizeRatio_);
  part->setGravity(gravity_);
  part->useGravity(useGravity_);

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
  particles_.clear();
}

bool ParticleSystem::hasDestroyTime()    const { return bool(destroyTime_); }

float ParticleSystem::getInterval()      const { return createInterval_; }
ofVec2f ParticleSystem::getSizeMin()     const { return sizeMin_; }
ofVec2f ParticleSystem::getSizeMax()     const { return sizeMax_; }
ofVec2f ParticleSystem::getVelocityMin() const { return velocityMin_; }
ofVec2f ParticleSystem::getVelocityMax() const { return velocityMax_; }

void ParticleSystem::setInterval(float interval)    { createInterval_ = interval; }
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
 : deltaTime_  ( 0     )
 , destroyTime_( 60    )
 , sizeRatio_  ( 1.0f  )
 , gravity_    ( 0.2f  )
 , useGravity_ ( false )
{}


void Particle::setup() {}

void Particle::update(float deltaTime) {
  deltaTime_ += deltaTime;

  // 重力を掛ける処理
  if (useGravity_) { vel_.y -= gravity_; }

  // 設定された加速度で移動する
  pos_ += vel_;

  // 時間経過で色を変化させる(startとendの色が違えば)
  r_.update(deltaTime);
  g_.update(deltaTime);
  b_.update(deltaTime);
  color_ = ofFloatColor(r_, g_, b_);
  
  animSizeX_.update(deltaTime);
  animSizeY_.update(deltaTime);
  size_ = ofVec2f(animSizeX_, animSizeY_);

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

  r_.setDuration(destroyTime_);
  r_.setCurve(LINEAR);
  r_.animateFromTo(startCol_.r, endCol_.r);

  g_.setDuration(destroyTime_);
  g_.setCurve(LINEAR);
  g_.animateFromTo(startCol_.g, endCol_.g);

  b_.setDuration(destroyTime_);
  b_.setCurve(LINEAR);
  b_.animateFromTo(startCol_.b, endCol_.b);
}

void Particle::setSizeRatio(float ratio) {
  sizeRatio_ = ratio;

  // 最終的な大きさを求めてanimateも設定
  ofVec2f ls = size_ * sizeRatio_;
  animSizeX_.setDuration(destroyTime_);
  animSizeX_.setCurve(LINEAR);
  animSizeX_.animateFromTo(size_.x, ls.x);

  animSizeY_.setDuration(destroyTime_);
  animSizeY_.setCurve(LINEAR);
  animSizeY_.animateFromTo(size_.y, ls.y);
}

void Particle::setGravity(float gravity) {
  gravity_ = gravity;
}

void Particle::useGravity(bool g) {
  useGravity_ = g;
}

/// ====================================================
///< @brief 仲間拡散時のぱーてくる
/// ====================================================
CspParticle::CspParticle() {}

void CspParticle::setup() {}

void CspParticle::update(float deltaTime) {}

void CspParticle::draw() {}

void CspParticle::onCollision(Actor* p_actor) {}
