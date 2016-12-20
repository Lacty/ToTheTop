
/**
 * @file   wemScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#pragma once


//! @brief テスト用シーンクラス
class WemScene : public ofxScene {
private:
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
