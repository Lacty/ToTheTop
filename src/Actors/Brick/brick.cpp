
/**
 * @file   brick.cpp
 * @brief  レンガ
 *
 * @author y.akira
 * @date   2016.12.29
 */

#include "precompiled.h"


Brick::Brick()
  : isFinishAnimating_( true )
{
	name_ = "Brick";
	tag_  =  BRICK ;
  
  color_ = ofColor(40, 40, 40, 230);
  round_ = 4;
}

void Brick::setup() {
  // アニメーションが終わった時の処理を指定
  y_.setAnimFinishedLambda(
    [&] () {
      shared_ptr<ParticleSystem> psys;
      psys = make_shared<ParticleSystem>(true);
      
      // system
      psys->setPos(pos_);
      psys->setSize(ofVec3f(size_.x, 0, 0));

      // time
      psys->setSysDestroyTime(0.1);
      psys->setPartDestroyTime(0.3);
      psys->setInterval(0.006);
      
      // param
      psys->setCreateSize(ofVec2f(2.f, 2.f), ofVec2f(4.0f, 4.0f));
      psys->setCreateVelocity(ofVec2f(-10.0f, 1.f), ofVec2f(10.0f, 10));
      psys->setAnimColor(ofColor(200, 50, 50), ofColor(50, 50, 50));
      
      // 縮小
      psys->setSizeRatio(0.4);
      
      // 重力
      psys->enableGravity();
      psys->setGravity(0.5);
      
      AddActor(psys);
    }
  );

	enableUpdate();
	enableCollision();
}

void Brick::update(float deltaTime) {
  if (isFinishAnimating_) return;
  
  isFinishAnimating_ = !(x_.isAnimating() && y_.isAnimating() && r_.isAnimating());

  x_.update(deltaTime);
  y_.update(deltaTime);
  r_.update(deltaTime);
  
  pos_.set(x_, y_);
  color_.r = float(r_) / 255;
}

void Brick::draw() {
	ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), round_);
}

void Brick::onCollision(Actor* c_actor) {}


const ofVec2f Brick::getFallPos() {
  if (isFinishAnimating_) {
    return pos_;
  }
  else {
    return ofVec2f(x_.getTargetValue(), y_.getTargetValue());
  }
}

/**
 * @brief 指定した位置に移動させる
 * @param [in] pos   移動先の地点
 * @param [in] curve イージングの種類
 * @param [in] time  アニメーションする時間
 */
void Brick::moveTo(const ofVec2f& pos, AnimCurve curve, float time) {
  x_.animateFromTo(pos_.x, pos.x);
  y_.animateFromTo(pos_.y, pos.y);
  r_.animateFromTo(300, 40);
  
  x_.setDuration(time);
  y_.setDuration(time);
  r_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
  r_.setCurve(curve);
  
  isFinishAnimating_ = false;
}

/**
 * @brief 指定した位置に移動させる
 * @param [in] x     移動先のx座標
 * @param [in] y     移動先のy座標
 * @param [in] curve イージングの種類
 * @param [in] time  アニメーションする時間
 */
void Brick::moveTo(float x, float y, AnimCurve curve, float time) {
  x_.animateFromTo(pos_.x, x);
  y_.animateFromTo(pos_.y, y);
  r_.animateFromTo(400, 40);
  
  x_.setDuration(time);
  y_.setDuration(time);
  r_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
  r_.setCurve(curve);
  
  isFinishAnimating_ = false;
}

/**
 * @brief 矩形の角を丸める数値を設定する
 * @param [in] r 角を丸める数値
 */
void Brick::setRectRound(float r) {
  round_ = r;
}

bool Brick::isAnimating() const {
  return !isFinishAnimating_;
}
