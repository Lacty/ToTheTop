
#pragma once
#include "scene.h"


class TestScene : public ofxScene {
private:
  
public:
  void setup();
  void update(float deltaTime);
  void draw();
  
  void keyPressed(int key);
};
