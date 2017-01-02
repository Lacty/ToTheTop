
/**
 * @file   player.h
 * @brief  プレイヤー
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


Player::Player() {
  gravity_   = 0.5f;
  jumpPow_   = 6.0f;
  moveSpeed_ = 1.0f;

  // 名前とサイズを設定
  name_ = "Player";
  pos_  = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
  size_ = ofVec2f(20, 20);
  vel_  = ofVec2f(0.0f, 0.0f);

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
  //stateMgr_->add(make_shared<DuckingState>(), this);

  // 前の状態にもどる
  // stateMgr_->pop();

  enableCollision();
  enableUpdate();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);

  float sync = deltaTime * ofGetFrameRate();
  vel_.y -= gravity_ * sync;
  pos_ += vel_     * sync;
  onFloor_ = false;
}

void Player::draw() {
  stateMgr_->draw(this);
  ofDrawRectangle(getRectangle());
}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);
}

void Player::gui() {
  if (ImGui::BeginMenu("Player_State")) {
    ImGui::SliderFloat("JumpPow", &jumpPow_, 0.5f, 30.0f);
    ImGui::SliderFloat("MoveSpeed", &moveSpeed_, 1.0f, 10.0f);
    ImGui::EndMenu();
  }
}
