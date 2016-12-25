
/**
 * @file     uiMeter.h
 * @brief    UI メーター
 *
 * @author   y.akira
 * @date     2016.12.25
 */

#include "precompiled.h"


uiMeter::uiMeter()
 : score_( 0 )
{
  name_ = "uiMeter";
}

void uiMeter::setup() {
  pos_    = ofVec3f(ofGetWindowWidth() * 0.5,
                    100, 0);
  
  player_  = FindActor("Player");
  
  // プレイヤーがnullだったらエラー
  assert(player_ != nullptr);
  
  // プレイヤーの現在位置で初期化
  score_   = player_->getPos().y;
  animAcc_ = 6.0f;
  
  anim_.reset(0.0f);
  font_.load("Font/mono.ttf", 30);
  
  enableUpdate();
}

void uiMeter::update(float deltaTime) {
  int playerY = player_->getPos().y;

  // プレイヤーの位置がスコアの数値より高ければ
  if (playerY > score_) {
    // スコアを更新
    score_ = playerY;
    
    // アニメーションリセット
    anim_.reset(0.0f);
    anim_.setCurve(EASE_OUT_BACK);
    anim_.animateTo(1);
  }
  
  anim_.update(deltaTime * animAcc_);
}

void uiMeter::draw() {
  string str = ofToString(score_);
  ofVec2f pos;
  pos.x = -font_.stringWidth(str) * 0.5;

  ofPushMatrix();
    ofTranslate(pos_);
    ofScale(max(0.8f, static_cast<float>(anim_)),
            max(0.8f, static_cast<float>(anim_)));
  
    font_.drawString(str, pos.x, pos.y);
  ofPopMatrix();
  
  gui();
}

void uiMeter::gui() {
  string str = "Score : " + ofToString(score_);

  ImGui::Begin("UI Meter");
    ImGui::Text("%s", str.c_str());
    ImGui::DragFloat2("Position", pos_.getPtr());
    ImGui::SliderFloat("Anim Acceleration", &animAcc_, 0, 10);
  ImGui::End();
}
