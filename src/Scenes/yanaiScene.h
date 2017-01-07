
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
  yCamera     cam_;
  BackGround  bg_;
  
  shared_ptr<Player> player_;
  shared_ptr<uiMeter> meter_;
  
  float camOffsetMin_;
  float camOffsetMax_;

  void moveCam();
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
  void keyPressed(int key) override;
};
