
/**
* @file   jumpingState.h
* @brief  ジャンプ状態
*
* @author wem
* @date   2016.12.21
*/

#include "precompiled.h"


/**
 *  @brief プレイヤーの上方向への加速度にジャンプ力を加算
 */
void JumpingState::setup(Player* player) {
  ofVec2f n_vel = player->getVel();
  n_vel.y = n_vel.y + player->getJumpPow();
  player->setVel(n_vel);
}

void JumpingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // 着地したらジャンプ状態を終了
  if (player->onFloor()) {
    stateMgr->pop();
  }

  // Xボタンを押したら、スキル状態へ遷移
  if (input.isPushing(Input::X)) {
    stateMgr->push();
    stateMgr->add(make_shared<TeleportState>(), player);
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {}

void JumpingState::draw(Player* player) {}
