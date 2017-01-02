
/**
 * @file   yCamera.h
 * @brief  2d用カメラ
 *
 * @author y.akria
 * @date   2016.12.30
 */

#pragma once


/**
 * @brief 2d用カメラ
 */
class yCamera {
private:
  ofVec2f pos_;
  ofVec2f offset_;

public:
  yCamera();
  virtual ~yCamera() {}
  
  void           setup();
  
  void           begin();
  void           end();
  
  const ofVec2f& getPos() const;
  
  void           setPos(const ofVec2f& pos);
};
