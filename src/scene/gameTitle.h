
#pragma once
#include "scene.h"


class GameTitle : public ofxScene {
private:

public:
  void setup();
  void update(float deltaTime);
  void draw();
  
  void keyPressed(int key);
};
