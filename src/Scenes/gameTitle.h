
/**
 * @file   gameTitle.h
 * @brief  ゲームタイトルのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


//! @brief ゲームタイトルのシーンクラスです
class GameTitle : public ofxScene {
private:
  ofTrueTypeFont font_;
  
  string         naviStr_;
  ofFloatColor   naviColor_;
  
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
};
