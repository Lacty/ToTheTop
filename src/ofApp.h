
/**
 * @file     ofApp.h
 * @brief    アプリ最上部
 * シーンのマネージメントを主に行います
 *
 * @author   y.akira
 * @date     2016.12.14
 */

#pragma once

/**
 * @brief oFに登録される最上部のアプリクラスです
 */
class ofApp : public ofBaseApp {
private:
  ofxSceneManager* sceneMgr_;  //!< シーンをマネージメントする変数
  float            acc_;       //!< ゲーム内時間を加減速させるための変数
  
  ofxImGui         gui_;       //!< これを使ってGuiの描画を可能にします
  
public:
  void setup();
  void update();
  void draw();

};
