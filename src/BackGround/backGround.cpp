
/**
 * @file     backGround.cpp
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#include "precompiled.h"


BackGround::BackGround() {}

void BackGround::windowResizeCallback(ofResizeEventArgs &resize) {
  windowSize_.x = resize.width;
  windowSize_.y = resize.height;
}

void BackGround::gui() {
  string str;

  ImGui::Begin("BackGround");
    str = "width  :" + ofToString(windowSize_.x, 0)
        + "height :" + ofToString(windowSize_.y, 0);
    ImGui::Text("%s", str.c_str());
  ImGui::End();
}

void BackGround::setup() {
  // 現在のウィンドウサイズを取得
  windowSize_ = ofGetWindowSize();

  // Callback関数を登録
  ofAddListener(ofEvents().windowResized, this, &BackGround::windowResizeCallback);
}

void BackGround::update() {}

void BackGround::draw() {
  ofBackgroundGradient(ofColor(120, 120, 120), ofColor(60, 60, 60));
  
  // Guiの描画
  gui();
}
