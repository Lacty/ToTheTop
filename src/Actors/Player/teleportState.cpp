
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
  currentAcc_ = g_local->FrameAcc();
  g_local->SetFrameAcc(player->getReduce());
  cursorPos_   = player->getPos();
  cursorSize_  = player->getSize();
}

void TeleportState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  if (input.isRelease(Input::X)) {
    player->setPos(cursorPos_);
    g_local->SetFrameAcc(currentAcc_);
    stateMgr->pop();
  }
}

//! 移動先の指定だけはフレームレート変更の影響を受けないようになっています
void TeleportState::update(float deltaTime, Player* player, ofxJoystick& input) {
  // スキル使用中の落下速度を一定の値にしてみる（試しに重力加速度の３倍に調整）
  if (player->getVel().y < -(player->getGravity() * 3)) { player->setVel(ofVec2f(player->getVel().x, -(player->getGravity() * 3))); }

  float sync = g_local->LastFrame() * ofGetFrameRate();
  cursorPos_ += cursorVel_ * sync;
  moveTelePos(player, input);
}

void TeleportState::draw(Player* player) {
  auto p_pos  = player->getPos();
  auto p_size = player->getSize();

  // スキルの有効範囲をPlayeの中心から円で表示
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawCircle((p_pos + (p_size / 2)), player->getTeleportCircle());
  ofPopMatrix();
  ofPopStyle();

  // 移動先を四角形で表示
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawPlane(cursorPos_.x + cursorSize_.x / 2,
              cursorPos_.y + cursorSize_.y,
              cursorSize_.x, cursorSize_.y);
  ofPopMatrix();
  ofPopStyle();
}


/**
* @brief Brickとの当たり判定がないと落下するので、ここにもBrickを貫通しない処理を追加
* @note  PlayerがActorに潰された場合の処理は不明なので後程追加します。
*/
void TeleportState::onCollision(Player* player, Actor* c_actor) {
  // プレイヤーと衝突判定を行うオブジェクトの必要パラメータを取得
  auto p_pos  = player->getPos();
  auto p_vel  = player->getVel();
  auto p_size = player->getSize();
  auto c_pos  = c_actor->getPos();
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

    // Playerの上辺がBrickの底辺とCollisionした場合
    else if (p_pos.y + p_vel.y < c_pos.y &&
             p_pos.y + p_size.y + p_vel.y > c_pos.y &&
             p_pos.x < c_pos.x + c_size.x &&
             p_pos.x + p_size.x > c_pos.x &&
             p_vel.y >= 0) {
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y - p_size.y));
    }

    // Playerの左辺がBrickの右辺とCollisionした場合
    else if (p_pos.x < c_pos.x + c_size.x &&
             p_pos.x + p_size.x > c_pos.x + c_size.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      player->setPos(ofVec2f(c_pos.x + c_size.x, p_pos.y));
    }

    // Playerの右辺がBrickの左辺とCollisionした場合
    else if (p_pos.x + p_size.x > c_pos.x &&
             p_pos.x < c_pos.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      player->setPos(ofVec2f(c_pos.x - p_size.x, p_pos.y));
    }
  }
}

// カーソルの移動処理
void TeleportState::moveTelePos(Player* player, ofxJoystick& input) {
  // 左右への移動
  if (input.isPushing(Input::Left) &&
      cursorPos_.x >= 0) {
    cursorVel_.x = -player->getCursorSpeed();
  }
  else if (input.isPushing(Input::Right) &&
           cursorPos_.x + cursorSize_.x <= ofGetWindowWidth()) {
    cursorVel_.x = player->getCursorSpeed();
  }
  else {
    cursorVel_.x = 0.0f;
  }

  // 上下への移動
  if (input.isPushing(Input::Down)) {
    cursorVel_.y = -player->getCursorSpeed();
  }
  else if (input.isPushing(Input::Up)) {
    cursorVel_.y = player->getCursorSpeed();
  }
  else {
    cursorVel_.y = 0.0f;
  }
}
