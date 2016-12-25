
/**
 * @file     uiMeter.h
 * @brief    UI メーター
 *
 * @author   y.akira
 * @date     2016.12.25
 */

#pragma once


class Actor;

class uiMeter : public uiBase {
private:
  int                score_;
  
  ofxAnimatableFloat anim_;
  float              animAcc_;
  
  ofTrueTypeFont     font_;
  
  shared_ptr<Actor>  player_;

  void gui();

public:
  uiMeter();
  ~uiMeter() {}
  
  void setup();
  void update(float deltaTime);
  void draw();
};
