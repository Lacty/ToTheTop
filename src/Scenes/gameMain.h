
/**
 * @file   gameMain.h
 * @brief  ゲームメインのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


//! ゲームメインのシーンクラスです
class GameMain : public ofxScene {
private:

public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
