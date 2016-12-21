
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
  // 左右キーの入力が無くなったら移動状態の削除
  if (!input.isPushing(Input::Left) && !input.isPushing(Input::Right)) {
    stateMgr->pop();
    stateMgr->remove(MOVING);
  }

  // ジャンプ状態へ遷移
  if (input.isPressed(Input::A)) {
    stateMgr->push();
    stateMgr->add(make_shared<JumpingState>(), player);
  }
}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofVec2f c_pos = player->getPos();
  ofVec2f c_vel = player->getVel();

  if (input.isPushing(Input::Left)) {
    ofVec2f n_pos = ofVec2f(c_pos.x - c_vel.x, c_pos.y);
    player->setPos(n_pos);
  }

  else if (input.isPushing(Input::Right)) {
    ofVec2f n_pos = ofVec2f(c_pos.x + c_vel.x, c_pos.y);
    player->setPos(n_pos);
  }
}

void MovingState::draw(Player* player) {}
