
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#pragma once


//! @brief テスト用シーンクラス
class NinjaScene : public ofxScene {
private:
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
