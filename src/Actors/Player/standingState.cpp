
/**
 * @file   standingState.h
 * @brief  立ち状態
 *
 * @author y.akira
 * @date   2016.12.17
 */

#include "precompiled.h"


void StandingState::setup(Player* player) {
  ofLog() << "standing setup()";
}

void StandingState::handleInput(Player* player, ofxJoystick& input) {
  ofLog() << "standing handleInput()";
}

void StandingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofLog() << "standing update()";
}

void StandingState::draw(Player* player) {
  ofLog() << "standing draw()";
}
