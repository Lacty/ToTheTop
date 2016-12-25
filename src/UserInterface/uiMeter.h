
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
  

public:
  uiMeter();
  ~uiMeter() {}
  
  void setup();
  void update(float deltaTime);
  void draw();
};
