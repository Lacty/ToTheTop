
#include "precompiled.h"


Player::Player() {
  name_ = "Player";
  size_ = ofVec2f(20, 20);
  
  joy_.setup(GLFW_JOYSTICK_1);
}

void Player::setup() {
  // updateを有効にする
  // この関数を呼ばなければupdateが呼ばれない
  enableUpdate();
  
  // collisionを有効にする
  // この関数を呼ばなければ当たり判定の処理から外される
  enableCollision();
}

void Player::update(float deltaTime) {}

void Player::draw() {
  ofSetColor(color_);
  ofDrawRectangle(getRectangle());
}

void Player::onCollisionEnter(Actor& c_actor) {}
