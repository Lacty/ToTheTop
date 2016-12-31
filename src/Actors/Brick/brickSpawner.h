
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
 * @note  Brickは(このクラス+WindowHeight)の位置に生成されます
 * @note  生成されたBrickはこのクラスの位置まで落下します
 */
class BrickSpawner : public Spawner {
private:

public:
  BrickSpawner();
  virtual ~BrickSpawner() {}
  
  void draw() override;
  
  void set(AnimCurve curve, float time);
};
