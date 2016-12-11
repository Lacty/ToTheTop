
#pragma once


class GameTitle : public ofxScene {
private:
  ofTrueTypeFont font_;
  
  string         naviStr_;
  ofFloatColor   naviColor_;
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
