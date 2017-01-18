
/**
 * @file   standingState.h
 * @brief  立ち状態
 *
 * @author y.akira
 * @date   2016.12.17
 */

#include "precompiled.h"


void StandingState::setup(Player* player) {}

void StandingState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
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

    // Xボタンを押したら、スキル状態へ遷移
    if (input.isPushing(Input::X) && player->canTeleport()) {
      player->setColorAnimFromTo();
      stateMgr->push();
      stateMgr->add(make_shared<TeleportState>(), player);
    }
  }
}

void StandingState::update(float deltaTime, Player* player, ofxJoystick& input) {
  // 潰れるエーモト
  if (input.isPressed(Input::Down) && player->onFloor()) {
    PlaySound(DUCK_START);

    player->getAnimY().setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
    player->getAnimY().setCurve(EASE_OUT);
    player->getAnimY().animateFromTo((player->getSize().y / 10) * 11,
                                     player->getSize().y * 2);
    player->getAnimY().setDuration(0.3);
  }
  // アニメーションが終わっている場合デフォルトのアニメーションを再度ループさせる
  if (!player->getAnimY().isAnimating()) {
    player->getAnimY().setRepeatType(LOOP_BACK_AND_FORTH);
    player->getAnimY().setCurve(BOUNCY);
    player->getAnimY().animateFromTo((player->getSize().y / 10) * 11,
                                     player->getSize().y);
    player->getAnimY().setDuration(0.6);
  }
}

void StandingState::draw(Player* player) {}

/**
 *  @brief 移動を一切行わなくても、立っているだけで起こる衝突判定はここに
 *  @note  PlayerがActorに潰された場合の処理は不明なので後程追加します。
 */
void StandingState::onCollision(Player* player, Actor* c_actor) {
  if (c_actor->getTag() == BRICK) {
    // プレイヤーと衝突判定を行うオブジェクトの必要パラメータを取得
    auto p_pos  = player->getPos();
    auto p_vel  = player->getVel();
    auto p_size = player->getSize();
    auto c_pos  = c_actor->getPos();
    auto c_size = c_actor->getSize();

    // Standing状態はonFloorがtrueの時しかありえないので条件文を省略
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
