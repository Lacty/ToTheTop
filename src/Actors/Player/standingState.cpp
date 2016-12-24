
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
  if (player->onFloor_ && input.isPressed(Input::A)) {
    stateMgr->push();
    stateMgr->add(make_shared<JumpingState>(), player);
    stateMgr->add(make_shared<MovingState>(), player);
  }
}

void StandingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  //ofLog() << "standing update()";
}

void StandingState::draw(Player* player) {
  //ofLog() << "standing draw()";
}

void StandingState::onCollision(Player* player, Actor* c_actor) {
  auto p_pos = player->getPos();
  auto c_pos = c_actor->getPos();

  // Brickに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Brickの上にPlayerの位置を修正
  if (p_pos.y > c_pos.y) {
    player->setVel(ofVec2f(player->getVel().x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_actor->getSize().y));
  }
}
