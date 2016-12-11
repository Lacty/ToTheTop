
#include "precompiled.h"


void GameMain::setup() {
  // gameMain.jsonから設定を読み込む
  ofxJSON json;
  json.open("game.json");
  string j_path = json["gameMainPath"].asString();
  json.open(j_path);
}

void GameMain::update(float deltaTime) {}

void GameMain::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Game Main", 20, 20);
}
