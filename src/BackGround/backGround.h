
/**
 * @file     backGround.h
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#pragma once


/**
 * @brief 宇宙をテーマにした背景を描画するクラス
 */
class BackGround {
private:
  ofVec2f windowSize_;
  
  // windowのサイズが変わった際に呼ばれる関数
  void windowResizeCallback(ofResizeEventArgs &resize);
  
  void gui();
  
public:
  BackGround();
  ~BackGround() {}
  
  void setup();
  void update();
  void draw();
};
