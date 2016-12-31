
/**
 * @file   gameTitle.h
 * @brief  ゲームタイトルのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

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
  naviStr_ = json["Navi"]["string"].asString();
  
  // 文字の色を読み込む
  for (int i = 0; i < 3; i++) {
    naviColor_[i] = json["Navi"]["color"][i].asFloat();
  }
}

void GameTitle::update(float deltaTime) {}

void GameTitle::draw() {
  // 文字列から描画時のサイズを算出
  float w = font_.stringWidth(naviStr_);
  
  ofSetColor(naviColor_);
  
  // naviを描画
  ofPushMatrix();
   ofTranslate(ofGetWidth() * 0.5 - w * 0.5, ofGetHeight() * 0.7);
   font_.drawString(naviStr_, 0, 0);
  ofPopMatrix();
}

void GameTitle::gui() {
  // Guiの描画
  if (ImGui::BeginMenu("Title")) {
    ImGui::ColorEdit3("Navi Color", &naviColor_.r);
  
    std::vector<char> arr(50);
    if (ImGui::InputText("Navi Str", arr.data(), 50)) {
      naviStr_ = arr.data();
    }
    ImGui::EndMenu();
  }
}
