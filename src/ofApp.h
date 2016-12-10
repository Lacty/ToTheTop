
#pragma once


class ofApp : public ofBaseApp {
private:
  ofxSceneManager* sceneMgr_;
  float acc_;
  
  ofxImGui gui_;
  
public:
  void setup();
  void update();
  void draw();
  
  void keyPressed(int key);
};
