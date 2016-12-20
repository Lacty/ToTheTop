
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
  pos_ = ofVec2f(80, 0);
  size_ = ofVec2f(20, 20);
  vel_ = ofVec2f(1.0f, 1.0f);
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
  // stateMgr_->add(make_shared<DuckingState>(), this);

  // 前の状態にもどる
  // stateMgr_->pop();

  enableUpdate();
  enableCollision();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);

  isHitLeft_ = false;
  isHitRight_ = false;
}

void Player::draw() {
  stateMgr_->draw(this);
  ofDrawRectangle(getRectangle());
}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);

  actorSearch(c_actor);
}

void Player::actorSearch(Actor* c_actor) {
  if (c_actor->getPos().x < pos_.x) { isHitLeft_ = true; }
  if (c_actor->getPos().x > pos_.x) { isHitRight_ = true; }
}
