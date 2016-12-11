
#pragma once


class Brick : public Actor {
private:
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void onCollisionEnter(Actor& c_actor) override;
};
