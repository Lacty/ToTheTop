
/**
 * @file     uiMeter.h
 * @brief    UI メーター
 *
 * @author   y.akira
 * @date     2016.12.25
 */

#pragma once


class uiMeter : public uiBase {
private:
  float score_;
  
  float deltaTime_;
  float interval_;
  float animTime_;
  
  ofxAnimatableFloat anim_;
  
  ofTrueTypeFont font_;
  
  void scoreUp() {}

public:
  uiMeter();
  ~uiMeter() {}
  
  void setup();
  void update(float deltaTime);
  void draw();
};
