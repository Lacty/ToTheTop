
/**
 * @file   wemScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void WemScene::setup() {}

void WemScene::update(float deltaTime) {}

void WemScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Wem Scene", 20, 20);
}
