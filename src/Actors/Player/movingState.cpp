﻿
/**
* @file   movingState.h
* @brief  移動状態
*
* @author wem
* @date   2016.12.20
*/

#include "precompiled.h"


void MovingState::setup(Player* player) {}

void MovingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // 入力が無く着地していたら左右への移動量を初期化し、移動状態を終了
  if (!input.isPushing(Input::Left) &&
      !input.isPushing(Input::Right) &&
      player->onFloor()) {
    player->setVel(ofVec2f(0.0f, player->getVel().y));
    stateMgr->pop();
  }

  // コントロール可能な状態なら遷移出来る
  if (player->canControl()) {
    // ジャンプ状態へ遷移
    if (player->onFloor() && input.isPressed(Input::A)) {
      player->setVel(ofVec2f(0.0f, player->getVel().y));
      stateMgr->push();
      stateMgr->add(make_shared<JumpingState>(), player);
      stateMgr->add(make_shared<MovingState>(), player);
    }

    // Xボタンを押したら、スキル状態へ遷移
    if (input.isPushing(Input::X) && player->canTeleport()) {
      player->setVel(ofVec2f(0, 0));
      stateMgr->push();
      stateMgr->add(make_shared<TeleportState>(), player);
    }
  }
}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofVec2f c_vel = player->getVel();

  if (input.isPushing(Input::Left) &&
      player->getPos().x >= 0) {
    c_vel.x = -player->getMoveSpeed();
    player->setVel(c_vel);
  }
  else if (input.isPushing(Input::Right) &&
           player->getPos().x + player->getSize().x <= ofGetWindowWidth()) {
    c_vel.x = player->getMoveSpeed();
    player->setVel(c_vel);
  }
  else {
    c_vel.x = 0.0f;
    player->setVel(c_vel);
  }
}

void MovingState::draw(Player* player) {}

/**
 *  @brief 移動状態で起こりうる上下左右の当たり判定を行います
 *  @note  ジャンプ状態と同時判定なので、MovingStateで一括処理
 */
void MovingState::onCollision(Player* player, Actor* c_actor) {
  // Brick以外の物と判定しないように制限
  if (c_actor->getTag() == BRICK) {
    // PlayerとBrickの必要パラメータを取得
    auto p_pos  = player->getPos();
    auto p_vel  = player->getVel();
    auto p_size = player->getSize();
    auto c_pos  = c_actor->getPos();
    auto c_vel  = c_actor->getVel();
    auto c_size = c_actor->getSize();

    // Playerの上辺がBrickの底辺とCollisionした場合
    if (p_pos.y + p_vel.y < c_pos.y &&
        p_pos.y + p_size.y + p_vel.y > c_pos.y &&
        p_pos.x < c_pos.x + c_size.x &&
        p_pos.x + p_size.x > c_pos.x &&
        p_vel.y >= 0) {
      // 挟まれた状態
      if (player->onFloor()) {
        player->isDead(true); // 死亡判定をtrueに
        player->setVel(ofVec2f(p_vel.x, 0.0f));
        player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
      }
      // 空中でぶつかった場合
      else {
        player->setVel(ofVec2f(p_vel.x, 0.0f));
        player->setPos(ofVec2f(p_pos.x, c_pos.y - p_size.y));
      }
    }

    // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
    // Brickの上にPlayerの位置を修正
    else if (p_pos.y + p_vel.y < c_pos.y + c_size.y &&
             (p_pos.y + p_size.y / 3) - p_vel.y > c_pos.y + c_size.y &&
             p_pos.x + (p_size.x / 7.5) < c_pos.x + c_size.x &&
             p_pos.x + p_size.x - (p_size.x / 7.5) > c_pos.x &&
             p_vel.y < 0) {
      player->onFloor(true);
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }

    // Playerの左辺がBrickの右辺とCollisionした場合
    else if (p_pos.x < c_pos.x + c_size.x &&
             p_pos.x + p_size.x > c_pos.x + c_size.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      // 画面外に押し出されないように調整
      if (c_pos.x + c_size.x >= ofGetWidth()) {
        player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
      }
      else {
        player->setPos(ofVec2f(c_pos.x + c_size.x, p_pos.y));
      }
    }

    // Playerの右辺がBrickの左辺とCollisionした場合
    else if (p_pos.x + p_size.x > c_pos.x &&
             p_pos.x < c_pos.x &&
             p_pos.y - p_vel.y * 2 < c_pos.y + c_size.y &&
             p_pos.y + p_size.y > c_pos.y) {
      player->setVel(ofVec2f(0.0f, p_vel.y));
      // 画面外に押し出されないように調整
      if (c_pos.x - p_size.x < 0) {
        player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
      }
      else {
        player->setPos(ofVec2f(c_pos.x - p_size.x, p_pos.y));
      }
    }

    // Brickに完全に埋まった場合
    if (p_pos.y - p_vel.y >= c_pos.y &&
        p_pos.y + p_size.y - p_vel.y <= c_pos.y + c_size.y &&
        p_pos.x >= c_pos.x &&
        p_pos.x + p_size.x <= c_pos.x + c_size.x) {
      player->isDead(true);
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }
  }
}
