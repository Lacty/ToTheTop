
/**
* @file   jumpingState.h
* @brief  ジャンプ状態
*
* @author wem
* @date   2016.12.21
*/

#include "precompiled.h"


void JumpingState::setup(Player* player) {
  ofVec2f c_pos = player->getPos();
  ofVec2f n_vel = player->getVel();
  n_vel.y = player->getRepulsion();
  player->setVel(n_vel);
  player->setPos(c_pos + n_vel);
}

void JumpingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // 着地したらジャンプ状態を終了
  if (player->onFloor()) {
    landing(player);
    stateMgr->pop();
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  // 落下処理
  auto c_vel = player->getVel();
  c_vel.y += 0.5f;
  player->setVel(c_vel);

  // 着地処理
  if (player->onFloor()) {
    landing(player);
  }
}

void JumpingState::draw(Player* player) {}

// 着地後の座標と加速度をデフォルトに戻す処理
void JumpingState::landing(Player* player) {
  auto c_pos = player->getPos();
  c_pos.y = 100;  // 仮の値
  player->setPos(c_pos);

  auto c_vel = player->getVel();
  c_vel.y = 0;
  player->setVel(c_vel);
}