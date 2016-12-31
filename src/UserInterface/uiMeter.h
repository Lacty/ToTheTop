
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

public:
  uiMeter();
  ~uiMeter() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
};
