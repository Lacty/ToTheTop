
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
  PlaySound(JUMP_START);

  player->getAnimX().setDuration(1);
  player->getAnimX().animateFromTo(player->getSize().x * 1.3,
                                   player->getSize().x);
  player->getAnimY().setDuration(1);
  player->getAnimY().animateFromTo(player->getSize().y / 1.2,
                                   player->getSize().y);
  ofVec2f n_vel = player->getVel();
  n_vel.y = n_vel.y + player->getJumpPow();
  player->setVel(n_vel);
}

void JumpingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // 着地したらジャンプ状態を終了
  if (player->onFloor()) {
    player->getAnimX().setDuration(1);
    player->getAnimX().animateFromTo(player->getSize().x,
                                     player->getSize().x);
    player->getAnimY().setDuration(0.6);
    player->getAnimY().animateFromTo((player->getSize().y / 10) * 11,
                                     player->getSize().y);
    player->setVel(ofVec2f(0.0f, 0.0f));
    stateMgr->pop();
  }

  // コントロール可能な状態なら遷移出来る
  if (player->canControl()) {
    // Xボタンを押したら、スキル状態へ遷移
    if (input.isPushing(Input::X) && player->canTeleport()) {
      player->setColorAnimFromTo();
      stateMgr->push();
      stateMgr->add(make_shared<TeleportState>(), player);
    }
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {}

void JumpingState::draw(Player* player) {}
