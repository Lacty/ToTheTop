
/**
 * @file     main.cpp
 * @brief    メイン。ω。
 *
 * @author   y.akira
 * @date     2016.12.14
 */

#include "precompiled.h"


int main() {
  // jsonから設定を読み込む
  ofxJSON json;
  json.open("user.json");
  
  int  w   = json["Window"]["width"].asInt();
  int  h   = json["Window"]["height"].asInt();
  bool f   = json["Window"]["fullScreen"].asBool();
  int  fps = json["Window"]["frameLimit"].asInt();

  // 設定されたボタン番号を読み込む
  string path = json["Input"]["path"].asString();
  Input::setup(path);

  ofSetupOpenGL(w, h, f ? OF_FULLSCREEN : OF_WINDOW);
  ofSetFrameRate(fps);
  
  ofRunApp(new ofApp());
}
