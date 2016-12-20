
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {}

void YanaiScene::update(float deltaTime) {}

void YanaiScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Yanai Scene", 20, 20);
}
