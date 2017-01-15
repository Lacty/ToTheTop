
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
  ofSoundPlayer sound_;
  
public:
  void setup() override;
  void exit() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
  void keyPressed(int key) override;
};
