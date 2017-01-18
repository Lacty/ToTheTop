
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {
  // スコアの取得
  auto list = GetScoreList();
  
  // スコアの追加
  list.emplace_back(make_unique<score_t>(1000, 6)); // スコア, 救出数
  list.emplace_back(make_unique<score_t>(100,  2));
  list.emplace_back(make_unique<score_t>(5555, 13));
  
  // スコアの保存
  SaveScoreList(move(list));
}

void YanaiScene::exit() {}

void YanaiScene::update(float deltaTime) {}

void YanaiScene::draw() {}

void YanaiScene::gui() {}

void YanaiScene::keyPressed(int key) {}
