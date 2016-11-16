
#include "playerState.h"
#include "player.h"


shared_ptr<PlayerState> PlayerState::finish = make_shared<PlayerState>();

shared_ptr<PlayerState> StandingState::handleInput(Player& player, ofxJoystick& input) {
  
  // to Jump
  if (input.isPressed(Button::JUMP)) {
    ofLog() << "standing -> jumping";
    player.addState(make_shared<MovingState>());
    return make_shared<JumpingState>();
  }
  
  // to Move
  if (input.isPressed(Button::LEFT)) {
    ofLog() << "standing -> moving";
    return make_shared<MovingState>();
  }
  if (input.isPressed(Button::RIGHT)) {
    ofLog() << "standing -> moving";
    return make_shared<MovingState>();
  }
  
  return nullptr;
}
void StandingState::update(Player& player, ofxJoystick& input) {}
void StandingState::entry(Player& player) {}


shared_ptr<PlayerState> MovingState::handleInput(Player& player, ofxJoystick& input) {
  // check for pushing any move button
  if (!input.isPushing(Button::LEFT) &&
      !input.isPushing(Button::RIGHT))
  {
    ofLog() << "moving -> back to previous";
    return PlayerState::finish;
  }
  
  if (input.isPressed(Button::JUMP)) {
    ofLog() << "moving -> jumping";
    return make_shared<JumpingState>();
  }
  
  return nullptr;
}
void MovingState::update(Player& player, ofxJoystick& input) {
  if (input.isPushing(Button::LEFT)) {
    ofVec2f newLocation = player.getPos();
    newLocation.x -= 1;
    player.setPos(newLocation);
  }
  
  if (input.isPushing(Button::RIGHT)) {
    ofVec2f newLocation = player.getPos();
    newLocation.x += 1;
    player.setPos(newLocation);
  }
}
void MovingState::entry(Player& player) {}


const int FLOOR = 0;
shared_ptr<PlayerState> JumpingState::handleInput(Player& player, ofxJoystick& input) {
  if (player.getPos().y <= FLOOR) {
    ofLog() << "jumping -> back to previous";
    return PlayerState::finish;
  }
  
  return nullptr;
}
void JumpingState::update(Player& player, ofxJoystick& input) {
  MovingState::update(player, input);
  
  vel_.y -= 0.8;
  ofVec2f newLocation = player.getPos() + vel_;
  if (newLocation.y <= FLOOR) { newLocation.y = FLOOR; }
  player.setPos(newLocation);
}
void JumpingState::entry(Player& player) {
  vel_.set(player.getJumpPow());
}