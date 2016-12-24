
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#pragma once


//! @brief テスト用シーンクラス
class YanaiScene : public ofxScene {
private:
  BackGround backGround_;
  
  ofImage image_;
  
  ofFloatColor rectColor_;
  ofFloatColor mojiColor_;
  float        rounder_;
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
