
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
  
  float              scale_;
  float              scaleMax_;
  float              scaleSpeed_;
  
  float              camY_;
  ofVec2f            offset_;
  
  ofTrueTypeFont     font_;
  
  weak_ptr<Actor>    player_;

public:
  uiMeter();
  virtual ~uiMeter() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
  void setCamY(float y);
  
  const int score() const;
};
