
/**
 * @file   brickSpawner.h
 * @brief  レンガ生成機
 *
 * @author y.akira
 * @date   2016.12.30
 */

#pragma once


/**
 * @brief Brick専用のスポナー
 * @note  生成されるBrickはこのクラスのパラメータを継承します
 * @note  生成されたBrickはこのクラスの位置まで落下します
 */
class BrickSpawner : public Spawner {
private:

public:
  BrickSpawner();
  virtual ~BrickSpawner() {}
  
  void draw() override;
  
  void set(const ofVec2f& startOffset, AnimCurve curve, float fallTime);
};
