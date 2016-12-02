
#pragma once
#include "scene.h"
#include "../actors/brick.h"


class TestScene : public ofxScene {
private:
  ofCamera cam_;

  list<Brick> bricks;
  
public:
  void setup();
  void update(float deltaTime);
  void draw();
  
  void keyPressed(int key);
};
