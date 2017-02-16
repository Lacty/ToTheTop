
/**
* @file     uiResque.h
* @brief    UI 救出数
*
* @author   wem
* @date     2017.2.13
*/

#include "precompiled.h"


uiResque::uiResque()
  : num_       (0)
  , currentNum_(0)
{
  name_ = "uiResque";
  tag_  = RESQUE;
}

void uiResque::setup() {
  color_ = ofColor(200, 200, 200);

  tex_.load("Texture/conspecies.png");
  texColor_ = ofColor::white - color_;

  // 画面サイズの変更に文字サイズを対応させる為に倍率を算出
  ofxJSON userJson;
  userJson.open("user.json");
  w_ = userJson["Window"]["width"].asInt();
  h_ = userJson["Window"]["height"].asInt();
  wRatio_ = ofGetWidth() / (float)w_;
  hRatio_ = ofGetHeight() / (float)h_;

  ofxJSON json;
  json.open("Actor/brickManager.json");
  auto column_ = json["Column"].asInt();
  auto size = (ofGetWindowWidth() / column_) * 0.15f;
  size = size * wRatio_;
  iconSize_ = ofVec2f(size, size);

  ofxJSON playerJson;
  playerJson.open("Actor/player.json");
  round_ = playerJson["Round"].asFloat();


  num_        = 0;
  currentNum_ = 0;
  scale_      = 1;
  scaleMax_   = 3.0;
  scaleSpeed_ = 0.2f;

  camY_ = 0;
  offset_.set(5, -5);

  font_.load("Font/mono.ttf", 20*wRatio_);

  enableUpdate();
}

void uiResque::update(float deltaTime) {
  pos_.x = (g_local->Width() / 10) * 8.75f;
  pos_.y = font_.getLineHeight();

  iconPos_.x = (g_local->Width() / 10) * 7.5f;
  iconPos_.y = iconSize_.y / 3;

  if (currentNum_ != num_) {
    currentNum_ = num_;
    scale_ = scaleMax_;
  }
  scale_ -= scaleSpeed_;
  scale_ = min(scale_, scaleMax_);
  scale_ = max(scale_, 1.0f);
}

void uiResque::draw() {
  // 仲間アイコン(外枠)
  ofPushMatrix();
  ofPushStyle();
  ofTranslate(iconPos_);
  ofDrawRectRounded(ofVec2f(0, 0),iconSize_.x, iconSize_.y, round_);
  ofPopStyle();
  ofPopMatrix();

  // 顔文字描画
  ofPushMatrix();
  ofPushStyle();
  ofTranslate(iconPos_);
  ofSetColor(texColor_);
  tex_.draw(0, 0, iconSize_.x, iconSize_.y);
  ofPopStyle();
  ofPopMatrix();

  // 数値の表示
  string str = ofToString(currentNum_);
  ofPushMatrix();
  ofTranslate(pos_);
  ofSetColor(color_);
  ofScale(scale_, scale_);
  font_.drawString(str, offset_.x, offset_.y);
  ofPopMatrix();

}

void uiResque::gui() {
  string str = "Resque : " + ofToString(num_);

  if (ImGui::BeginMenu("UI Resque")) {
    ImGui::Text("%s", str.c_str());
    ImGui::EndMenu();
  }
}

void uiResque::setCamY(float y) {
  camY_ = y;
}

//! 救出者数の加算に利用
void uiResque::setNum(float num) {
  num_ = num;
}

//! 現在の救出者数を返す
const int uiResque::getNum() const {
  return currentNum_;
}
