
/**
 * @file   duckingState.h
 * @brief  しゃがみ状態
 *
 * @author y.akira
 * @date   2016.12.18
 */

#include "precompiled.h"


// Ducking中のPlayerが潰れたように見せる為にAnimatableの数値を調整
void DuckingState::setup(Player* player) {}

void DuckingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {}

void DuckingState::update(float deltaTime, Player* player, ofxJoystick& input) {}

void DuckingState::draw(Player* player) {}

void DuckingState::onCollision(Player* player, Actor* c_actor) {}