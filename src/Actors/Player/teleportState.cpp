
/**
* @file   teleportState.h
* @brief  スキル状態
*
* @author wem
* @date   2016.1.2
*/

#include "precompiled.h"

//! TeleportStateに遷移した瞬間にフレームレートを下げる
void TeleportState::setup(Player* player) {
  g_local->SetFrameAcc(0.1f);
  circle_ = 100;
  telePos_ = player->getPos();
  teleSize_ = player->getSize();
  moveSpeed_ = 3.0f;
}

void TeleportState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  if (input.isRelease(Input::Y)) {
    player->setPos(telePos_);
    g_local->SetFrameAcc(1);
    stateMgr->pop();
  }
}

//! 移動先の指定だけはフレームレート変更の影響を受けないようになっています
void TeleportState::update(float deltaTime, Player* player, ofxJoystick& input) {
  float sync = g_local->LastFrame() * ofGetFrameRate();
  telePos_ += teleVel_ * sync;
  moveTelePos(input);
}

void TeleportState::draw(Player* player) {
  auto p_pos = player->getPos();
  auto p_size = player->getSize();

  // スキルの有効範囲をPlayeの中心から円で表示
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawCircle((p_pos + (p_size / 2)), circle_);
  ofPopMatrix();
  ofPopStyle();

  // 移動先を四角形で表示
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawPlane(telePos_.x + teleSize_.x / 2,
    telePos_.y + teleSize_.y,
    teleSize_.x, teleSize_.y);
  ofPopMatrix();
  ofPopStyle();
}


/**
* @brief Brickとの当たり判定がないと落下するので、ここにもBrickを貫通しない処理を追加
* @note  PlayerがActorに潰された場合の処理は不明なので後程追加します。
*/
void TeleportState::onCollision(Player* player, Actor* c_actor) {
  // Actorに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Actorの上にPlayerの位置を修正
  if (player->getPos().y < c_actor->getPos().y + c_actor->getSize().y &&
    player->getPos().y + player->getSize().y > c_actor->getPos().y + c_actor->getSize().y &&
    player->getPos().x < c_actor->getPos().x + c_actor->getSize().x &&
    player->getPos().x + player->getSize().x > c_actor->getPos().x &&
    player->getVel().y < 0) {
    player->onFloor(true);
    player->setVel(ofVec2f(player->getVel().x, 0.0f));
    player->setPos(ofVec2f(player->getPos().x,
      c_actor->getPos().y + c_actor->getSize().y));
  }
}

void TeleportState::moveTelePos(ofxJoystick& input) {
  // 左右への移動
  if (input.isPushing(Input::Left)) {
    teleVel_.x = -moveSpeed_;
  }
  else if (input.isPushing(Input::Right)) {
    teleVel_.x = moveSpeed_;
  }
  else {
    teleVel_.x = 0.0f;
  }

  // 上下への移動
  if (input.isPushing(Input::Down)) {
    teleVel_.y = -moveSpeed_;
  }
  else if (input.isPushing(Input::Up)) {
    teleVel_.y = moveSpeed_;
  }
  else {
    teleVel_.y = 0.0f;
  }
}
