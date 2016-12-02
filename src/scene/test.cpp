
#include "test.h"


void TestScene::setup() {
  // testScene.jsonから設定を読み込む
  ofxJson::get().load("game.json");
  string j_path = ofxJson::getString("testScenePath");
  ofxJson::get().load(j_path);
}

void TestScene::update(float deltaTime) {}

void TestScene::draw() {
  ofDrawBitmapString("Test Scene", 20, 20);
}

void TestScene::keyPressed(int key) {}
