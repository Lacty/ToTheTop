
/**
 * @file     backGround.cpp
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#include "precompiled.h"


BackGround::BackGround()
  : interval_(0.5)
  , deltaTime_(0)
{
  inColor_  = ofColor(80, 80, 80);
  outColor_ = ofColor(40, 40, 40);
}

void BackGround::windowResizeCallback(ofResizeEventArgs &resize) {
  windowSize_.x = resize.width;
  windowSize_.y = resize.height;
}

void BackGround::gui() {
  ImGui::Begin("BackGround");
  
  ImGui::ColorEdit3("In  Color", &inColor_.r);
  ImGui::ColorEdit3("Out Color", &outColor_.r);
  
  ImGui::SliderFloat("Interval", &interval_, 0, 1);
  ImGui::ColorEdit3("Star Color", &starColor_.r);
  
  ImGui::End();
}

void BackGround::setup() {
  // 現在のウィンドウサイズを取得
  windowSize_ = ofGetWindowSize();

  // Callback関数を登録
  ofAddListener(ofEvents().windowResized, this, &BackGround::windowResizeCallback);
}

void BackGround::update(float deltaTime) {
  deltaTime_ += deltaTime;
  
  for (auto& star : stars_) {
    star->update(deltaTime);
  }
  
  if (deltaTime_ > interval_) {
    deltaTime_ = 0;
    ofVec3f pos(ofRandom(windowSize_.x * 0.3, windowSize_.x * 1.3), 0, 0);
    ofVec3f vel(ofRandom(-5.0f, -2.0f), ofRandom(2.0f, 5.0f), 0);
  
    stars_.emplace_back(
      make_unique<Star>(
        pos,
        vel,
        starColor_,
        1.0,           ///< 時間経過で伸びる速度(height)
        0.1,           ///< 時間経過で縮む速度(width)
        0.1f,          ///< heightに対して節目がどこにあるか(0~1)
        20,            ///< width
        150            ///< height
      )
    );
  }
}

void BackGround::draw() {
  ofBackgroundGradient(inColor_, outColor_);
  
  for (auto& star : stars_) {
    star->draw();
  }
  // Guiの描画
  gui();
}


Star::Star(const ofVec3f& pos, const ofVec3f& vel, const ofFloatColor& color,
           float extend,
           float shrink,
           float clause,
           float width, float height)
  : pos_   (pos   )
  , vel_   (vel   )
  , color_ (color )
  , extend_(extend)
  , shrink_(shrink)
  , clause_(clause)
  , width_ (width )
  , height_(height)
{}

void Star::update(float deltaTime) {
  pos_    += vel_;
  height_ += extend_;
  width_  -= shrink_;
}

void Star::draw() {
  const int vDim = 3;
  const int vNum = vDim * 4;
  const int cDim = 4;
  const int cNum = cDim * 4;
  
  ofVec3f left = vel_.getCrossed(ofVec3f(0, 0, 1));
  left.normalize();
  
  ofVec3f p2 = (-vel_.getNormalized() * height_ * clause_) + (-left * width_ * 0.5) + pos_;
  ofVec3f p3 = (-vel_.getNormalized() * height_ * clause_) + ( left * width_ * 0.5) + pos_;
  ofVec3f p4 = -vel_.getNormalized() * height_ + pos_;
  
  float vtx[vNum] = {
    pos_.x, pos_.y, pos_.z,
      p2.x,   p2.y,   p2.z,
      p3.x,   p3.y,   p3.z,
      p4.x,   p4.y,   p4.z,
  };
  
  float color[cNum] = {
    color_.r, color_.g, color_.b, color_.a,
    color_.r, color_.g, color_.b, color_.a,
    color_.r, color_.g, color_.b, color_.a,
    color_.r, color_.g, color_.b,        0,
  };
  
  glVertexPointer(vDim, GL_FLOAT, 0, vtx);
  glColorPointer(cDim, GL_FLOAT, 0, color);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}













