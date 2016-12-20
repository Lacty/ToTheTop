
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
  stateMgr_ = make_shared<StateManager>();
}

void Player::setup() {
  // 初期状態を設定
  // 立ち状態を追加
  stateMgr_->add(make_shared<StandingState>(), this);
  
  // 次の状態へ移行
  // stateMgr_->push();
  
  // しゃがみ状態を追加
  stateMgr_->add(make_shared<DuckingState>(), this);
  
  // 前の状態にもどる
  // stateMgr_->pop();
  
  enableUpdate();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);
}

void Player::draw() {
  stateMgr_->draw(this);
}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);
}
