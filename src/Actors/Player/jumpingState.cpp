
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
  if (player->onFloor_) {
    stateMgr->pop();
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {}

void JumpingState::draw(Player* player) {}

void JumpingState::onCollision(Player* player, Actor* c_actor){
  auto p_pos = player->getPos();
  auto c_pos = c_actor->getPos();

  // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Brickの上にPlayerの位置を修正
  if (p_pos.y > c_pos.y) {
    player->setVel(ofVec2f(player->getVel().x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_actor->getSize().y));
  }
}
