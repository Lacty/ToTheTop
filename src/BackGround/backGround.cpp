
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

void BackGround::setup() {
  // 現在のウィンドウサイズを取得
  windowSize_ = ofGetWindowSize();

  // Callback関数を登録
  ofAddListener(ofEvents().windowResized, this, &BackGround::windowResizeCallback);
}

void BackGround::update() {}

void BackGround::draw() {}
