
/**
 * @file   player.h
 * @brief  プレイヤー
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


Player::Player() {
  // 名前とサイズを設定
  name_ = "Player";
  pos_ = ofVec2f(80, 0);
  size_ = ofVec2f(20, 20);
  vel_ = ofVec2f(0.01f, 0.01f);
  joy_.setup(GLFW_JOYSTICK_1);
  stateMgr_ = make_shared<StateManager>();
}

void Player::setup() {
  // 初期状態を設定
  // 立ち状態を追加
  stateMgr_->add(make_shared<StandingState>(), this);

  // 次の状態へ移行
  // stateMgr_->push();

  // しゃがみ状態を追加
  // stateMgr_->add(make_shared<DuckingState>(), this);

  // 前の状態にもどる
  // stateMgr_->pop();

  enableUpdate();
  enableCollision();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);

  isHitLeft_ = false;
  isHitRight_ = false;
}

void Player::draw() {
  stateMgr_->draw(this);
  ofDrawRectangle(getRectangle());
}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);
  // 衝突した方向を判定
  if (c_actor->getPos().x < pos_.x) { isHitLeft_ = true; }
  if (c_actor->getPos().x > pos_.x) { isHitRight_ = true; }

  pullBrick(c_actor);
}

void Player::pullBrick(Actor* c_actor) {
  // 左右のどちらかでヒットした状態で決定ボタンを押したらキャッチ
  // 左右両方の判定がtrueの場合、Actorに挟まれているので発動しない
  if (isHitLeft_ && joy_.isPushing(1) || isHitRight_ && joy_.isPushing(1))
  {
    // 通常移動が発生しないよう当たり判定をtrueにし続ける
    isHitLeft_ = true;
    isHitRight_ = true;

    // キャッチした状態で右を入力したら
    if (joy_.isPushing(Input::Right)) {
      ofVec2f newLocation = c_actor->getPos();
      newLocation.x += vel_.x;
      pos_.x += vel_.x;
      c_actor->setPos(newLocation);
    }

    // キャッチした状態で左を入力したら
    else if (joy_.isPushing(Input::Left)) {
      ofVec2f newLocation = c_actor->getPos();
      newLocation.x -= vel_.x;
      pos_.x -= vel_.x;
      c_actor->setPos(newLocation);
    }
  }
}
