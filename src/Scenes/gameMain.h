
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
private:
  yCamera     cam_;
  BackGround  bg_;

  weak_ptr<Player>   player_;
  weak_ptr<uiMeter>  meter_;
  weak_ptr<uiResque> resque_;
  float camOffsetMin_;
  float camOffsetMax_;

  float resultTimer_;

  void moveCam();

public:
  void setup() override;
  void exit() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
};
