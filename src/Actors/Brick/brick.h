#pragma once


class StateManager;

class Brick : public Actor {
private:
  ofImage brickImg_;
public:
  Brick();

  void setup() override;
  void update(float deltaTime) override;
  void draw() override;

  void onCollision(Actor* c_actor) override;
};
