
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

  // Xボタンを押したら、スキル状態へ遷移
  if (input.isPushing(Input::X)) {
    stateMgr->push();
    stateMgr->add(make_shared<TeleportState>(), player);
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
  // Actorに上からぶつかったら加速度を０に(左右への移動量はそのまま)
  // Actorの上にPlayerの位置を修正
  if (c_actor->getTag() == BRICK &&
      player->getPos().y < c_actor->getPos().y + c_actor->getSize().y &&
      player->getPos().y + player->getSize().y > c_actor->getPos().y + c_actor->getSize().y &&
      player->getPos().x < c_actor->getPos().x + c_actor->getSize().x &&
      player->getPos().x + player->getSize().x > c_actor->getPos().x &&
      player->getVel().y < 0) {
    player->onFloor(true);
    player->setVel(ofVec2f(player->getVel().x, 0.0f));
    player->setPos(ofVec2f(player->getPos().x,
                           c_actor->getPos().y + c_actor->getSize().y));
  }
}
