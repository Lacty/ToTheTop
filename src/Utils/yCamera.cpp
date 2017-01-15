
/**
 * @file   yCamera.cpp
 * @brief  2d用カメラ
 *
 * @author y.akria
 * @date   2016.12.30
 */

#include "precompiled.h"


yCamera::yCamera() {}


void yCamera::setup() {
  offset_.set(0, ofGetWindowHeight());
}

/**
 * @brief カメラの処理を実行
 * @note  物体を描画する前に呼び出してください
 */
void yCamera::begin() {
  ofPushMatrix();
  ofScale(-1, 1);
  ofTranslate(pos_);
  ofScale(-1, 1);
  ofTranslate(offset_);
  ofScale(1, -1);
}

/**
 * @brief カメラの処理を終了
 * @note  begin()のあとに必ず呼び出してください
 */
void yCamera::end() {
  ofPopMatrix();
}

const ofVec2f& yCamera::getPos() const {
  return pos_;
}

void yCamera::setPos(const ofVec2f& pos) {
  pos_ = pos;
}
