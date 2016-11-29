
#include "player.h"


Player::Player() {
  jumpPow_.set(0, 10);

  joy_.setup(GLFW_JOYSTICK_1);
  state_.push_back(make_shared<StandingState>());
}

void Player::handleInput() {
  shared_ptr<PlayerState> state = state_.back()->handleInput(*this, joy_);
  if (state) {
    if (state == PlayerState::finish) {
      // err : state stack will become nothing
      assert(state_.at(1) != nullptr);
      state_.pop_back();
    } else {
      state_.push_back(state);
    }
    
    state_.back()->entry(*this);
  }
}

void Player::update() {
  handleInput();
  state_.back()->update(*this, joy_);
}

void Player::draw() {
  ofDrawBox(pos_, 50);
}

const ofVec2f& Player::getPos() const { return pos_; }
const ofVec2f& Player::getJumpPow() const { return jumpPow_; }

void Player::setPos(const ofVec2f& pos) { pos_.set(pos); }

void Player::addState(const shared_ptr<PlayerState>& state) {
  state_.push_back(state);
}
