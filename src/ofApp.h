
#pragma once
#include "ofMain.h"
#include "ofxSceneManager.h"


class ofApp : public ofBaseApp {
private:
  ofxSceneManager* sceneManager;
  
public:
  void setup();
  void update();
  void draw();
  
  void keyPressed(int key);
};
