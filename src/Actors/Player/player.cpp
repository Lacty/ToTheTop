
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
  stateMgr_->add(make_shared<StandingState>(), this);
  stateMgr_->push();
  stateMgr_->add(make_shared<DuckingState>(), this);
  stateMgr_->pop();
  stateMgr_->push();
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
