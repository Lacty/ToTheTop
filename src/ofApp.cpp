
/**
 * @file     ofApp.cpp
 * @brief    アプリ最上部
 * シーンのマネージメントを主に行います
 *
 * @author   y.akira
 * @date     2016.12.14
 */

#include "precompiled.h"


/**
 * @brief アプリ起動時に一度だけ呼ばれる
 * シーンの追加やGuiのセットアップなどを行う
 */
void ofApp::setup() {
  // load json
  ofxJSON json;
  json.open("game.json");

  sceneMgr_ = ofxSceneManager::instance();
  
  // シーンを追加
  sceneMgr_->addScene(new GameTitle(), TITLE);
  sceneMgr_->addScene(new GameMain(),  GAME);
  sceneMgr_->addScene(new Sandbox(),   SANDBOX);
  
  // 指定したデフォルトのシーンへ遷移
  int ds = json["defaultScene"].asInt();
  sceneMgr_->goToScene(ds, false, false);
  
  // 遷移のフェード時間を設定
  float dt = json["fade"]["dropTime"].asFloat();
  float dr = json["fade"]["riseTime"].asFloat();
  sceneMgr_->setCurtainDropTime(dt);
  sceneMgr_->setCurtainRiseTime(dr);
  
  acc_ = json["acceleration"].asFloat();

  gui_.setup();
}

/**
 * @brief 毎フレーム呼ばれる
 * シーンに仮想ゲーム内時間
 */
void ofApp::update() {
  float dt = ofGetLastFrameTime() * acc_;
  sceneMgr_->update(dt);
}

/**
 * @brief 毎フレーム呼ばれる
 * シーンの描画やGuiの描画を行なっている
 */
void ofApp::draw() {
  gui_.begin();
  
   sceneMgr_->draw();
  
   ImGui::Begin("Root");
    ImGui::Text("%s", string("width  :" + ofToString(ofGetWidth())).c_str());
    ImGui::Text("%s", string("height :" + ofToString(ofGetHeight())).c_str());
    ImGui::Text("%s", string("FPS :" + ofToString(ofGetFrameRate() , 1)).c_str());
  
    ImGui::SliderFloat("Acceleration", &acc_, 0, 3);
  
    if (ImGui::Button("scene change to GameTitle")) { sceneMgr_->goToScene(TITLE);   }
    if (ImGui::Button("scene change to GameMain"))  { sceneMgr_->goToScene(GAME);    }
    if (ImGui::Button("scene change to Sandbox"))   { sceneMgr_->goToScene(SANDBOX); }
   ImGui::End();
  
  gui_.end();
}
