
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {
  auto uiRank = make_shared<uiScoreRank>();
  uiRank->enableDrawCurrentScore();
  uiRank->setCurrentScore(114514);
  AddUI(uiRank);
}

void YanaiScene::exit() {
  ClearUIs();
}

void YanaiScene::update(float deltaTime) {
  UpdateUIs(deltaTime);
}

void YanaiScene::draw() {
  DrawUIs();
}

void YanaiScene::gui() {}

void YanaiScene::keyPressed(int key) {}
