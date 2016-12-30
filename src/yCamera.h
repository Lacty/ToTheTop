
/**
 * @file   2dCamera.h
 * @brief  2d用カメラ
 *
 * @author y.akria
 * @date   2016.12.30
 */

#pragma once


class yCamera {
private:
  ofVec2f pos_;
  ofVec2f offset_;

public:
  yCamera();
  virtual ~yCamera() {}
  
  void setup();
  void begin();
  void end();
};
