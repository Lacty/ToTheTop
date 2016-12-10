
#include "../precompiled.h"


void Player::setup() {
  name_ = "Player";
  size_ = ofVec2f(20, 20);

  finishSetup();
  enableUpdate();
  enableCollision();
}

void Player::update(float deltaTime) {
  pos_.x += deltaTime * 10.f;
}

void Player::draw() {
  ofDrawRectangle(getRectangle());
}


void Player::onCollisionEnter(Actor& c_actor) {
  ofLog() << "collision to " << c_actor.getName();
  c_actor.destroy();
}
