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
  // 入力が無く、着地していたら移動量の初期化と移動状態を終了
  if (!input.isPushing(Input::Left) &&
      !input.isPushing(Input::Right) &&
      player->onFloor()) {
        auto n_vel = player->getVel();
        n_vel = ofVec2f(0.0f, 0.0f);
        player->setVel(n_vel);
        stateMgr->pop();
  }

  // ジャンプ状態へ遷移(何度呼ばれても良いように、呼び出す度に一度削除)
  if (player->onFloor() && input.isPressed(Input::A)) {
    stateMgr->remove(JUMPING);
    stateMgr->add(make_shared<JumpingState>(), player);
  }
}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofVec2f c_vel = player->getVel();

  if (input.isPushing(Input::Left)) {
    c_vel.x = -1.0f;
    player->setVel(c_vel);
  }
  else if (input.isPushing(Input::Right)) {
    c_vel.x = 1.0f;
    player->setVel(c_vel);
  }
  else {
    c_vel.x = 0.0f;
    player->setVel(c_vel);
  }
}

void MovingState::draw(Player* player) {}