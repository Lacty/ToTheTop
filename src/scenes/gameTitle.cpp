
#include "ofxSceneManager.h"
#include "gameTitle.h"


void GameTitle::setup() {
  // gameTitle.jsonから設定を読み込む
  ofxJson::get().load("game.json");
  string j_path = ofxJson::getString("gameTitlePath");
  ofxJson::get().load(j_path);
  
  // fontの設定をjsonから読み込む
  string path = ofxJson::getString("Navi/fontPath");
  int size = ofxJson::getInt("Navi/fontSize");
  font_.load(path, size);
  
  // 表示するnaviの文字列を読み込む
  navi_ = ofxJson::getString("Navi/string");
}

void GameTitle::update(float deltaTime) {}

void GameTitle::draw() {
  // 文字列から描画時のサイズを算出
  float w = font_.stringWidth(navi_);
  
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
