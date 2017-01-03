
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
  circle_    = 100;
  telePos_   = player->getPos();
  teleSize_  = player->getSize();
  moveSpeed_ = 3.0f;
}

void TeleportState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  if (input.isRelease(Input::X)) {
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
  auto p_pos  = player->getPos();
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
  // プレイヤーと衝突判定を行うオブジェクトの必要パラメータを取得
  auto p_pos = player->getPos();
  auto p_vel = player->getVel();
  auto p_size = player->getSize();
  auto c_pos = c_actor->getPos();
  auto c_size = c_actor->getSize();

  // Brick以外の物と判定しないように制限
  if (c_actor->getTag() == BRICK) {
    // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
    // Brickの上にPlayerの位置を修正
    if (p_pos.y + p_vel.y < c_pos.y + c_size.y &&
        (p_pos.y + p_size.y / 3) - p_vel.y > c_pos.y + c_size.y &&
        p_pos.x + (p_size.x / 10) <= c_pos.x + c_size.x &&
        p_pos.x + p_size.x - (p_size.x / 10) >= c_pos.x &&
        p_vel.y < 0) {
      player->onFloor(true);
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }

    // Playerの上辺がActorの底辺とCollisionした場合
    else if (p_pos.y + p_vel.y < c_pos.y &&
             p_pos.y + p_size.y + p_vel.y > c_pos.y &&
             p_pos.x < c_pos.x + c_size.x &&
             p_pos.x + p_size.x > c_pos.x &&
             p_vel.y >= 0) {
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y - p_size.y));
    }

    // Playerの左辺がActorの右辺とCollisionした場合
    else if (p_pos.x < c_pos.x + c_size.x &&
             p_pos.x + p_size.x > c_pos.x + c_size.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      player->setPos(ofVec2f(c_pos.x + c_size.x, p_pos.y));
    }

    // Playerの右辺がActorの左辺とCollisionした場合
    else if (p_pos.x + p_size.x > c_pos.x &&
             p_pos.x < c_pos.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      player->setPos(ofVec2f(c_pos.x - p_size.x, p_pos.y));
    }
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
