
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
  tag_  = METER;
}

void uiMeter::setup() {
  color_ = ofColor(200, 200, 200);
  
  score_      = 0;
  scale_      = 1;
  scaleMax_   = 1.6;
  scaleSpeed_ = 0.2f;
  
  camY_ = 0;
  offset_.set(5, -5);
  
  font_.load("Font/mono.ttf", 20);
  
  enableUpdate();
}

void uiMeter::update(float deltaTime) {
  if (!player_.lock()) {
    player_  = FindActor("Player");
    return;
  }

  if (auto player = player_.lock()) {
    int playerY = player->getPos().y;

    // プレイヤーの位置がスコアの数値より高ければ
    if (playerY > score_) {
      // スコアを更新
      score_ = playerY;
      scale_ = scaleMax_;
    }
  
    scale_ -= scaleSpeed_;
    scale_ = min(scale_, scaleMax_);
    scale_ = max(scale_, 1.0f);
  
    pos_.y = g_local->Height() - (score_ - camY_) - player->getSize().y;
  }
}

void uiMeter::draw() {
  string str = ofToString(score_);

  ofPushMatrix();
    ofTranslate(pos_);
  
    ofSetColor(color_.r, color_.g, color_.b, 200);
    ofDrawLine(0, 0, g_local->Width(), 0);
  
    ofSetColor(color_);
    ofScale(scale_, scale_);
    font_.drawString(str, offset_.x, offset_.y);
  ofPopMatrix();
}

void uiMeter::gui() {
  string str = "Score : " + ofToString(score_);

  if (ImGui::BeginMenu("UI Meter")) {
      ImGui::Text("%s", str.c_str());
    ImGui::EndMenu();
  }
}

void uiMeter::setCamY(float y) {
  camY_ = y;
}

//! 現在のスコアを返す
const int uiMeter::score() const {
  return score_;
}
