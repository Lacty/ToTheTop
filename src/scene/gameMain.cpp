
#include "ofxSceneManager.h"
#include "gameMain.h"


void GameMain::setup() {
  // gameMain.jsonから設定を読み込む
  ofxJson::get().load("game.json");
  string j_path = ofxJson::getString("gameMainPath");
  ofxJson::get().load(j_path);
}

void GameMain::update(float deltaTime) {}

void GameMain::draw() {
  ofDrawBitmapString("Game Main", 20, 20);
}

void GameMain::keyPressed(int key) {}
