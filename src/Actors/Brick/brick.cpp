
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
	enableUpdate();
	enableCollision();
}

void Brick::update(float deltaTime) {
  if (isFinishAnimating_) return;
  
  isFinishAnimating_ = !(x_.isAnimating() && y_.isAnimating());

  x_.update(deltaTime);
  y_.update(deltaTime);
  
  pos_.set(x_, y_);
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
  
  x_.setDuration(time);
  y_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
  
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
  
  x_.setDuration(time);
  y_.setDuration(time);
  
  x_.setCurve(curve);
  y_.setCurve(curve);
  
  isFinishAnimating_ = false;
}

/**
 * @brief 矩形の角を丸める数値を設定する
 * @param [in] r 角を丸める数値
 */
void Brick::setRectRound(float r) {
  round_ = r;
}
