
#include "ofApp.h"
#include "scene/gameTitle.h"
#include "scene/gameMain.h"


void ofApp::setup() {
  // load json
  ofxJson::get().load("game.json");

  sceneMgr_ = ofxSceneManager::instance();
  
  // シーンを追加
  sceneMgr_->addScene(new GameTitle(), TITLE);
  sceneMgr_->addScene(new GameMain(),  GAME);
  
  // 指定したデフォルトのシーンへ遷移
  sceneMgr_->goToScene(ofxJson::getInt("defaultScene"), false, false);
  
  // 遷移のフェード時間を設定
  sceneMgr_->setCurtainDropTime(ofxJson::getFloat("fade/dropTime"));
  sceneMgr_->setCurtainRiseTime(ofxJson::getFloat("fade/riseTime"));
  
  acc_ = ofxJson::getFloat("acceleration");

  gui_.setup();
}

void ofApp::update() {
  float dt = ofGetLastFrameTime() * acc_;
  sceneMgr_->update(dt);
}

void ofApp::draw() {
  sceneMgr_->draw();
  
  // guiの描画
  gui_.begin();
   ImGui::Begin("Root");
    ImGui::Text("%s", string("width  :" + ofToString(ofGetWidth())).c_str());
    ImGui::Text("%s", string("height :" + ofToString(ofGetHeight())).c_str());
    ImGui::Text("%s", string("FPS :" + ofToString(ofGetFrameRate() , 1)).c_str());
  
    ImGui::SliderFloat("Acceleration", &acc_, 0, 3);
  
    if (ImGui::Button("scene change to GameTitle")) { sceneMgr_->goToScene(TITLE); }
    if (ImGui::Button("scene change to GameMain"))  { sceneMgr_->goToScene(GAME);  }
   ImGui::End();
  gui_.end();
}


void ofApp::keyPressed(int key) {
  sceneMgr_->keyPressed(key);
}
