
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
  pos_    = ofVec3f(g_local->HalfWidth(),
                    g_local->Height() * 0.15, 0);
  
  color_  = ofColor::black;
  
  player_  = FindActor("Player");
  
  score_   = 0;
  animAcc_ = 6.0f;
  
  anim_.reset(0.0f);
  font_.load("Font/mono.ttf", 30);
  
  enableUpdate();
}

void uiMeter::update(float deltaTime) {
  if (!player_) {
    player_  = FindActor("Player");
    return;
  }

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
  
    ofSetColor(color_);
    font_.drawString(str, pos.x, pos.y);
  ofPopMatrix();
}

void uiMeter::gui() {
  string str = "Score : " + ofToString(score_);

  if (ImGui::BeginMenu("UI Meter")) {
      ImGui::Text("%s", str.c_str());
      ImGui::DragFloat2("Position", pos_.getPtr());
      ImGui::SliderFloat("Anim Acceleration", &animAcc_, 0, 10);
    ImGui::EndMenu();
  }
}

//! 現在のスコアを返す
const int uiMeter::score() const {
  return score_;
}
