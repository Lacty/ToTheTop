
/**
* @file   movingState.h
* @brief  �ړ����
*
* @author wem
* @date   2016.12.20
*/

#include "precompiled.h"


void MovingState::setup(Player* player) {}

void MovingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {}

void MovingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  // enableCollision()������Actor�������ɖ�����Έړ�
  if (!player->isHitLeft_ && input.isPushing(Input::Left)) {
    float newLocation = player->getPos().x - player->getVel().x;
    player->setPos(ofVec2f(newLocation, player->getPos().y));
  }

  // enableCollision()������Actor���E���ɖ�����Έړ�
  else if (!player->isHitRight_ && input.isPushing(Input::Right)) {
    float newLocation = player->getPos().x + player->getVel().x;
    player->setPos(ofVec2f(newLocation, player->getPos().y));
  }
}

void MovingState::draw(Player* player) {}
