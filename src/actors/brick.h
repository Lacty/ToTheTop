
#pragma once
#include "actor.h"


// 上から落ちてくる足場となるレンガ
class Brick : public Actor {
private:
  bool active_;

public:
  Brick();
  Brick(const ofVec3f& pos, const ofVec3f& size, bool active);
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  bool& active();
};
