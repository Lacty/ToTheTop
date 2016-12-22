
/**
* @file   jumpingState.h
* @brief  ジャンプ状態
*
* @author wem
* @date   2016.12.21
*/

#include "precompiled.h"


void JumpingState::setup(Player* player) {
  ofVec2f n_vel = player->getVel();
  n_vel.y = n_vel.y + player->getJumpPow();
  player->setVel(n_vel);
}

void JumpingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // 着地したらジャンプ状態を終了
  if (player->onFloor()) {
    auto c_pos = player->getPos();
    c_pos.y = 100;  // 仮の値
    player->setPos(c_pos);

    auto c_vel = player->getVel();
    c_vel.y = 0;
    player->setVel(c_vel);

    stateMgr->pop();
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  MovingState::update(deltaTime, player, input);
  // 落下処理
  auto c_vel = player->getVel();
  c_vel.y += 0.5f;
  player->setVel(c_vel);

  auto c_pos = player->getPos();
  c_pos.y += c_vel.y;
  player->setPos(c_pos);
}

void JumpingState::draw(Player* player) {}
