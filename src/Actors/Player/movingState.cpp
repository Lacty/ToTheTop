
/**
* @file   movingState.h
* @brief  移動状態
*
* @author wem
* @date   2016.12.20
*/

#include "precompiled.h"


void MovingState::setup(Player* player) {}

void MovingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  // enableCollision()をしたActorが左側に無ければ移動
  if (input.isPushing(Input::Left)) {
    float newLocation = player->getPos().x - player->getVel().x;
    player->setPos(ofVec2f(newLocation, player->getPos().y));
  }

  // enableCollision()をしたActorが右側に無ければ移動
  else if (input.isPushing(Input::Right)) {
    float newLocation = player->getPos().x + player->getVel().x;
    player->setPos(ofVec2f(newLocation, player->getPos().y));
  }
}

void MovingState::draw(Player* player) {}
