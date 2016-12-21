
/**
* @file   jumpingState.h
* @brief  ƒWƒƒƒ“ƒvó‘Ô
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
  if (player->onFloor()) {
    ofLog() << "On Floor";
    auto c_pos = player->getPos();
    c_pos.y = 100;  // ‰¼‚Ì’l
    player->setPos(c_pos);

    auto c_vel = player->getVel();
    c_vel.y = 0;
    player->setVel(c_vel);

    stateMgr->pop();
    stateMgr->remove(JUMPING);
  }
}

void JumpingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  MovingState::update(deltaTime, player, input);
  // —Ž‰ºˆ—
  auto c_vel = player->getVel();
  c_vel.y += 0.5f;
  player->setVel(c_vel);

  auto c_pos = player->getPos();
  c_pos.y += c_vel.y;
  player->setPos(c_pos);
}

void JumpingState::draw(Player* player) {}
