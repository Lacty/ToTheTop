
#pragma once
#include "ofMain.h"
#include "ofxJoystick.h"
#include "playerState.h"


class Player {
private:
  ofVec2f pos_;
  
  ofxJoystick joy_;
  deque<shared_ptr<PlayerState>> state_;
  
  void handleInput();
  
public:
  Player();
  
  void update();
  void draw();
  
  const ofVec2f& getPos() const;
  
  void setPos(const ofVec2f& pos);
};