
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void NinjaScene::setup() {}

void NinjaScene::update(float deltaTime) {}

void NinjaScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Ninja Scene", 20, 20);
}
