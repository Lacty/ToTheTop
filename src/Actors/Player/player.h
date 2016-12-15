
#pragma once


class Player : public Actor {
private:
  ofxJoystick joy_;
  
public:
  Player();
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void onCollisionEnter(Actor& c_actor) override;
};
