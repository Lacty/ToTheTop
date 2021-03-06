﻿
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {
  cam_.setup();
  AddActor(make_shared<ParticleSystem>());
  
  AddUI(make_shared<uiScoreRank>());
}

void YanaiScene::exit() {
  ClearActors();
  ClearUIs();
}

void YanaiScene::update(float deltaTime) {
  UpdateActors(deltaTime);
  UpdateUIs(deltaTime);
}

void YanaiScene::draw() {
  cam_.begin();
  DrawActors();
  cam_.end();
  
  DrawUIs();
}

void YanaiScene::gui() {
  DrawActorsGui();
}

void YanaiScene::keyPressed(int key) {}
