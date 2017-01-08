
/**
 * @file   duckingState.h
 * @brief  しゃがみ状態
 *
 * @author y.akira
 * @date   2016.12.18
 */

#include "precompiled.h"


// Ducking中のPlayerが潰れたように見せる為にAnimatableの数値を調整
void DuckingState::setup(Player* player) {
  player->getAnimX().setDuration(0.7);
  player->getAnimY().setDuration(0.7);
  player->getAnimY().animateFromTo(player->getSize().y*2,
                                   (player->getSize().y / 4) * 6);
}

void DuckingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  // ボタンを離したらStandingへ戻る
  // Animatableの数値をデフォルトに戻す
  if (!input.isPushing(Input::Down)) {
    player->getAnimX().setDuration(1);
    player->getAnimX().setDuration(1);
    player->getAnimY().animateFromTo(player->getSize().y,
                                     (player->getSize().y / 10) * 9);
    stateMgr->pop();
  }

  // コントロール可能な状態なら遷移出来る
  if (player->canControl()) {
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
}

void DuckingState::update(float deltaTime, Player* player, ofxJoystick& input) {}

void DuckingState::draw(Player* player) {}

void DuckingState::onCollision(Player* player, Actor* c_actor) {
  if (c_actor->getTag() == BRICK) {
    // プレイヤーと衝突判定を行うオブジェクトの必要パラメータを取得
    auto p_pos  = player->getPos();
    auto p_vel  = player->getVel();
    auto p_size = player->getSize();
    auto c_pos  = c_actor->getPos();
    auto c_vel  = c_actor->getVel();
    auto c_size = c_actor->getSize();

    // 状態はonFloorがtrueの時しかありえないので条件文を省略
    if (p_pos.y + p_vel.y < c_pos.y &&
      p_pos.y + p_size.y + p_vel.y > c_pos.y &&
      p_pos.x < c_pos.x + c_size.x &&
      p_pos.x + p_size.x > c_pos.x &&
      p_vel.y >= 0) {
      player->isDead(true); // 死亡判定をtrueに
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }

    // Actorに上からぶつかったら加速度を０に(左右への移動量はそのまま)
    // Actorの上にPlayerの位置を修正
    else if (p_pos.y + p_vel.y < c_pos.y + c_size.y &&
      (p_pos.y + p_size.y / 3) - p_vel.y > c_pos.y + c_size.y &&
      p_pos.x + (p_size.x / 10) <= c_pos.x + c_size.x &&
      p_pos.x + p_size.x - (p_size.x / 10) >= c_pos.x &&
      p_vel.y < 0) {
      player->onFloor(true);
      player->setVel(ofVec2f(p_vel.x, 0.0f));
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }

    // Brickに完全に埋まった場合
    if (p_pos.y - p_vel.y >= c_pos.y &&
      p_pos.y + p_size.y - p_vel.y <= c_pos.y + c_size.y &&
      p_pos.x >= c_pos.x &&
      p_pos.x + p_size.x <= c_pos.x + c_size.x) {
      player->isDead(true);
      player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
    }
  }
}