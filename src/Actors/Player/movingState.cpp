
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
      player->onFloor_) {
        player->setVel(ofVec2f(0.0f, player->getVel().y));
        stateMgr->pop();
  }

  // ジャンプ状態へ遷移
  if (player->onFloor_ && input.isPressed(Input::A)) {
    stateMgr->push();
    stateMgr->add(make_shared<JumpingState>(), player);
    stateMgr->add(make_shared<MovingState>(), player);
  }
}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofVec2f c_vel = player->getVel();

  if (input.isPushing(Input::Left)) {
    c_vel.x = -player->getMoveSpeed();
    player->setVel(c_vel);
  }
  else if (input.isPushing(Input::Right)) {
    c_vel.x = player->getMoveSpeed();
    player->setVel(c_vel);
  }
  else {
    c_vel.x = 0.0f;
    player->setVel(c_vel);
  }
}

void MovingState::draw(Player* player) {}

void MovingState::onCollision(Player* player, Actor* c_actor) {
  auto p_pos = player->getPos();
  auto p_vel = player->getVel();
  auto c_pos = c_actor->getPos();
  auto c_size = c_actor->getSize();

  // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Brickの上にPlayerの位置を修正
  if (p_pos.y > c_pos.y) {
    player->setVel(ofVec2f(p_vel.x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
  }
}
