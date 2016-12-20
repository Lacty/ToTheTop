
/**
 * @file   duckingState.h
 * @brief  しゃがみ状態
 *
 * @author y.akira
 * @date   2016.12.18
 */

#include "precompiled.h"


void DuckingState::setup(Player* player) {
  ofLog() << "ducking setup()";
}

void DuckingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  ofLog() << "ducking handleInput()";
}

void DuckingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofLog() << "ducking update()";
}

void DuckingState::draw(Player* player) {
  ofLog() << "ducking draw()";
}
