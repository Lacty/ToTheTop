
/**
 * @file   player.h
 * @brief  プレイヤー
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


Player::Player() {
  // 名前とサイズを設定
  name_ = "Player";
  size_ = ofVec2f(20, 20);
  
  joy_.setup(GLFW_JOYSTICK_1);
}

void Player::setup() {

  enableUpdate();
  enableCollision();
}

void Player::update(float deltaTime) {
  pos_.x += 1;
}

void Player::draw() {
  ofSetColor(color_);
  ofDrawRectangle(getRectangle());
}

void Player::onCollisionEnter(Actor& c_actor) {
  ofLog() << "my name   : " << getName();
  ofLog() << "collision : " << c_actor.getName();
  c_actor.destroy();
}
