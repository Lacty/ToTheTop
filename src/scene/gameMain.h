
#pragma once
#include "scene.h"


class GameMain : public ofxScene {
private:

public:
  void setup();
  void update(float deltaTime);
  void draw();
  
  void keyPressed(int key);
};
