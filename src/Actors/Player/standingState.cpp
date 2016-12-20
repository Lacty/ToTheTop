
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

void StandingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  ofLog() << "standing handleInput()";

  // Brickとぶつかっていない状態なら左右へ移動
  if (!player->isHitLeft_ && input.isPressed(Input::Left) || !player->isHitRight_ && input.isPressed(Input::Right)) {
    stateMgr->push();
    stateMgr->add(make_shared<MovingState>(), player);
  }
  // 左右キーの入力が無くなったら移動状態の削除
  if (!input.isPressed(Input::Left) && !input.isPressed(Input::Right)) {
    stateMgr->remove(MOVING);
  }
}

void StandingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  ofLog() << "standing update()";
}

void StandingState::draw(Player* player) {
  ofLog() << "standing draw()";
}
