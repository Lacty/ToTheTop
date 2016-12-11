
#pragma once


class GameTitle : public ofxScene {
private:
  ofTrueTypeFont font_;
  
  // "push any key"のようなnaviの文字列
  string navi_;
  
public:
  void setup();
  void update(float deltaTime);
  void draw();
  
};
