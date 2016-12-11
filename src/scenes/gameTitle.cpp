
#include "precompiled.h"


void GameTitle::setup() {
  // gameTitle.jsonから設定を読み込む
  ofxJSON json;
  json.open("game.json");
  string j_path = json["gameTitlePath"].asString();
  json.open(j_path);
  
  // fontの設定をjsonから読み込む
  string path = json["Navi"]["fontPath"].asString();
  int    size = json["Navi"]["fontSize"].asInt();
  font_.load(path, size);
  
  // 表示するnaviの文字列を読み込む
  navi_ = json["Navi"]["string"].asString();
  
  AddActor(make_shared<Player>());
  AddActor(make_shared<Brick>());
}

void GameTitle::update(float deltaTime) {
  UpdateActors(deltaTime);
}

void GameTitle::draw() {
  // 文字列から描画時のサイズを算出
  float w = font_.stringWidth(navi_);
  
  DrawActors();
  
  // naviを描画
  ofPushMatrix();
   ofTranslate(ofGetWidth() * 0.5 - w * 0.5, ofGetHeight() * 0.7);
   font_.drawString(navi_, 0, 0);
  ofPopMatrix();
}

void GameTitle::keyPressed(int key) {
  // 何かキーが押されたら次のシーンへ遷移する
  getManager()->goToScene(GAME);
}
