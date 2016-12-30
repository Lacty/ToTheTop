
/**
 * @file   2dCamera.cpp
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

void yCamera::begin() {
  ofPushMatrix();
  ofScale(-1, 1);
  ofTranslate(pos_);
  ofScale(-1, 1);
  ofTranslate(offset_);
  ofScale(1, -1);
}

void yCamera::end() {
  ofPopMatrix();
}
