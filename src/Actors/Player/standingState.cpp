
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
  if (player->onFloor() && input.isPressed(Input::A)) {
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

/**
 *  @brief 移動を一切行わなくても、立っているだけで起こる衝突判定はここに
 *  @note  PlayerがActorに潰された場合の処理は不明なので後程追加します。
 */
void StandingState::onCollision(Player* player, Actor* c_actor) {
  auto p_pos  = player->getPos();
  auto p_vel  = player->getVel();
  auto p_size = player->getSize();
  auto c_pos  = c_actor->getPos();
  auto c_size = c_actor->getSize();

  // Actorに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Actorの上にPlayerの位置を修正
  if (p_pos.y < c_pos.y + c_size.y &&
      p_pos.y + p_size.y > c_pos.y + c_size.y &&
      p_pos.x < c_pos.x + c_size.x &&
      p_pos.x + p_size.x > c_pos.x &&
      p_vel.y < 0) {
    player->onFloor(true);
    player->setVel(ofVec2f(p_vel.x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
  }
}
