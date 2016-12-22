
/**
 * @file   standingState.h
 * @brief  立ち状態
 *
 * @author y.akira
 * @date   2016.12.17
 */

#include "precompiled.h"


void StandingState::setup(Player* player) {
  //ofLog() << "standing setup()";
}

void StandingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  //ofLog() << "standing handleInput()";
  // 左右どちらかのキーが入力されたら移動状態に
  if (input.isPushing(Input::Left) || input.isPushing(Input::Right)) {
    stateMgr->push();
    stateMgr->add(make_shared<MovingState>(), player);
  }

  // Ａボタンを押したら、ジャンプ状態に遷移(移動状態も併せ持つ)
  if (input.isPressed(Input::A)) {
    stateMgr->push();
    stateMgr->add(make_shared<JumpingState>(), player);
  }
}

void StandingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  //ofLog() << "standing update()";
}

void StandingState::draw(Player* player) {
  //ofLog() << "standing draw()";
}
