
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
  auto p_pos  = player->getPos();
  auto p_vel  = player->getVel();
  auto p_size = player->getSize();
  auto c_pos  = c_actor->getPos();
  auto c_size = c_actor->getSize();

  // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Brickの上にPlayerの位置を修正
  if (p_pos.y > c_pos.y &&
    p_pos.x < c_pos.x + c_size.x &&
    p_pos.x + p_size.x > c_pos.x) {
    player->setVel(ofVec2f(p_vel.x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
  }


  // プレイヤーの左辺がアクターの右辺より左側ならCollision
  if (p_pos.x < c_pos.x + c_size.x &&
    p_pos.x + p_size.x > c_pos.x + c_size.x &&
    p_pos.y < c_pos.y + c_size.y / 2) {
    player->setVel(ofVec2f(0.0f, p_vel.y));
    player->setPos(ofVec2f(c_pos.x + c_size.x, p_pos.y));
  }

  // プレイヤーの右辺がアクターの左辺より右側ならCollision
  if (p_pos.x + p_size.x > c_pos.x &&
    p_pos.x < c_pos.x &&
    p_pos.y < c_pos.y + c_size.y / 2) {
    player->setVel(ofVec2f(0.0f, p_vel.y));
    player->setPos(ofVec2f(c_pos.x - p_size.x, p_pos.y));
  }
}
