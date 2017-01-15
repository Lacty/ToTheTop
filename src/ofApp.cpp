
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
  
  g_local->Setup();
  sceneMgr_ = ofxSceneManager::instance();
  
  // シーンを追加
  sceneMgr_->addScene(new GameTitle(),  TITLE);
  sceneMgr_->addScene(new GameMain(),   GAME);
  sceneMgr_->addScene(new YanaiScene(), YANAI); //< テストシーン
  sceneMgr_->addScene(new WemScene(),   WEM);   //< テストシーン
  sceneMgr_->addScene(new NinjaScene(), NINJA); //< テストシーン
  
  // 指定したデフォルトのシーンへ遷移
  int ds = json["defaultScene"].asInt();
  sceneMgr_->goToScene(ds, false, false);
  
  // 遷移のフェード時間を設定
  float dt = json["Fade"]["dropTime"].asFloat();
  float dr = json["Fade"]["riseTime"].asFloat();
  sceneMgr_->setCurtainDropTime(dt);
  sceneMgr_->setCurtainRiseTime(dr);

  acc_ = g_local->FrameAcc();

  gui_.setup();
  
  // 全てのサウンドを読み込む
  LoadAllSound("Sound/sound.json");
}

/**
 * @brief 毎フレーム呼ばれる
 * シーンに仮想ゲーム内時間
 */
void ofApp::update() {
  if (g_local->Stop) { return; }
  
  float dt = g_local->AccedLastFrame();
  sceneMgr_->update(dt);
  
  ofSoundUpdate(); // サウンド更新
}

/**
 * @brief 毎フレーム呼ばれる
 * シーンの描画やGuiの描画を行なっている
 */
void ofApp::draw() {
  sceneMgr_->draw();
  gui();
}

void ofApp::gui() {
  gui_.begin();
  
  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("Root")) {
    ImGui::Text("%s", string("width  :" + ofToString(g_local->Width())).c_str());
    ImGui::Text("%s", string("height :" + ofToString(g_local->Height())).c_str());
    ImGui::Text("%s", string("FPS :" + ofToString(g_local->FrameRate() , 1)).c_str());
    
    if (ImGui::SliderFloat("Acceleration", &acc_, 0, 3)) {
      g_local->SetFrameAcc(acc_);
    }
    
    if (ImGui::Button("GameTitle"))  { sceneMgr_->goToScene(TITLE);  }
    if (ImGui::Button("GameMain"))   { sceneMgr_->goToScene(GAME);   }
    if (ImGui::Button("YanaiScene")) { sceneMgr_->goToScene(YANAI);  }
    if (ImGui::Button("WemScene"))   { sceneMgr_->goToScene(WEM);    }
    if (ImGui::Button("NinjaScene")) { sceneMgr_->goToScene(NINJA);  }
    ImGui::EndMenu();
  }
  
  sceneMgr_->gui();
  
  ImGui::EndMainMenuBar();
  
  gui_.end();
}


void ofApp::keyPressed(int key) {
  sceneMgr_->keyPressed(key);
  if (key == 's') {
    g_local->Stop = !g_local->Stop;
  }
}

void ofApp::keyReleased(int key) {
  sceneMgr_->keyReleased(key);
}
