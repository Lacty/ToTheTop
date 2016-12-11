
#include "precompiled.h"


Player::Player() {
  joy_.setup(GLFW_JOYSTICK_1);
}

void Player::setup() {}

void Player::update(float deltaTime) {}

void Player::draw() {}

void Player::onCollisionEnter(const shared_ptr<Actor>& c_actor) {}
