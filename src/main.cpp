
/**
 * @file     main.cpp
 * @brief    メイン
 *
 * @author   y.akira
 * @date     2016.12.14
 */

#include "precompiled.h"


int main() {
  // jsonから設定を読み込む
  ofxJSON json;
  json.open("user.json");
  
  int  w   = json["window"]["width"].asInt();
  int  h   = json["window"]["height"].asInt();
  bool f   = json["window"]["fullScreen"].asBool();
  int  fps = json["window"]["frameLimit"].asInt();

  ofSetupOpenGL(w, h, f ? OF_FULLSCREEN : OF_WINDOW);
  ofSetFrameRate(fps);
  
  ofRunApp(new ofApp());
}
