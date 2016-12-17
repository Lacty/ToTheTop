
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
  pos_  = ofVec2f(0, 0);
  size_ = ofVec2f(20, 20);
  
  joy_.setup(GLFW_JOYSTICK_1);
  mgr_ = make_shared<StateManager>();
}

void Player::setup() {
  mgr_->add(make_shared<StandingState>(), this);
  enableUpdate();
}

void Player::update(float deltaTime) {
  mgr_->update(deltaTime, this, joy_);
}

void Player::draw() {
  mgr_->draw(this);
}

void Player::onCollision(Actor* c_actor) {
  mgr_->onCollision(this, c_actor);
}
