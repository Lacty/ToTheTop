
#pragma once
#include "ofxJoystick.h"


enum Button {
  JUMP = 2,
  LEFT = 15,
  RIGHT = 13
};

class Player;

class PlayerState {
public:
  virtual ~PlayerState() {};
  
  virtual shared_ptr<PlayerState> handleInput(Player& player, ofxJoystick& input) {};
  
  virtual void update(Player& player, ofxJoystick& input) {};
  virtual void entry(Player& player) {};
  
  static shared_ptr<PlayerState> finish;
};

class StandingState : public PlayerState {
public:
  shared_ptr<PlayerState> handleInput(Player& player, ofxJoystick& input) override;
  void update(Player& player, ofxJoystick& input) override;
  void entry(Player& player) override;
};

class MovingState : public PlayerState {
public:
  shared_ptr<PlayerState> handleInput(Player& player, ofxJoystick& input) override;
  void update(Player& player, ofxJoystick& input) override;
  void entry(Player& player) override;
};

class JumpingState : public MovingState {
private:
  ofVec2f vel_;

public:
  shared_ptr<PlayerState> handleInput(Player& player, ofxJoystick& input) override;
  void update(Player& player, ofxJoystick& input) override;
  void entry(Player& player) override;
};