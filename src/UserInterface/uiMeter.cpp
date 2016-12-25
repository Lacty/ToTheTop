
/**
 * @file     uiMeter.h
 * @brief    UI メーター
 *
 * @author   y.akira
 * @date     2016.12.25
 */

#include "precompiled.h"


uiMeter::uiMeter() {
  name_ = "uiMeter";
  ofLog() << "uiMeter()";
}

void uiMeter::setup() {
  ofLog() << "uiMeter::setup()";
  
  score_ = 0;
  
  deltaTime_ = 0;
  interval_ = 0.5;
  animTime_ = 6;
  
  anim_.reset(0.0f);
  
  font_.load("Font/MarkerFelt.ttf", 30);
  
  enableUpdate();
}

void uiMeter::update(float deltaTime) {
  ofLog() << "uiMeter::update()";
  
  deltaTime_ += deltaTime;
  if (deltaTime_ > interval_) {
    deltaTime_ = 0;
    
    anim_.reset(0.0f);
    anim_.setCurve(EASE_OUT_BACK);
    anim_.animateTo(1);
    
    score_++;
  }
  
  anim_.update(deltaTime * animTime_);
}

void uiMeter::draw() {
  ofLog() << "uiMeter::draw()";
  
  ofPushMatrix();
    ofTranslate(100, 50);
    ofScale(max(0.8f, static_cast<float>(anim_)),
            max(0.8f, static_cast<float>(anim_)));
    font_.drawString(ofToString(score_), 0, 0);
    ofDrawBitmapString("UI METER", 0, 0);
  ofPopMatrix();
  
  ImGui::Begin("Ease Test");
    string str;
  
    str = "Score : " + ofToString(score_);
    ImGui::Text("%s", str.c_str());
  
    str = "DeltaTime : " + ofToString(deltaTime_);
    ImGui::Text("%s", str.c_str());
  
    ImGui::DragFloat("Interval", &interval_);
    ImGui::DragFloat("Anim Time", &animTime_);
  ImGui::End();
}
