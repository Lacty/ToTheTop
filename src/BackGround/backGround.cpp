
/**
 * @file     backGround.cpp
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#include "precompiled.h"


BackGround::BackGround()
  : interval_ ( 0.4 )
  , deltaTime_( 0   )
  , widthMin_ ( 20  )
  , widthMax_ ( 50  )
  , heightMin_( 100 )
  , heightMax_( 200 )
  , extendMin_( 0.4 )
  , extendMax_( 0.8 )
{
  inColor_     = ofColor(80, 80, 80);
  outColor_    = ofColor(40, 40, 40);
  spawnPosMin_ = ofVec2f(0, ofGetWindowHeight());
  spawnPosMax_ = ofVec2f(ofGetWindowSize());
  velocityMin_ = ofVec2f(-0.3, -6);
  velocityMax_ = ofVec2f( 0.3, -3);
  starColor_   = ofFloatColor(0.2, 0.2, 0.2);
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
  if (ImGui::TreeNode("Spawn Position")) {
    ImGui::InputFloat2("min", spawnPosMin_.getPtr());
    ImGui::InputFloat2("max", spawnPosMax_.getPtr());
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Velocity")) {
    ImGui::InputFloat2("min", velocityMin_.getPtr());
    ImGui::InputFloat2("max", velocityMax_.getPtr());
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Width")) {
    ImGui::InputFloat("min", &widthMin_);
    ImGui::InputFloat("max", &widthMax_);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Height")) {
    ImGui::InputFloat("min", &heightMin_);
    ImGui::InputFloat("max", &heightMax_);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Extend")) {
    ImGui::InputFloat("min", &extendMin_);
    ImGui::InputFloat("max", &extendMax_);
    ImGui::TreePop();
  }
  ImGui::ColorEdit3("Star Color", &starColor_.r);
  
  ImGui::End();
}

void BackGround::setup() {
  // 現在のウィンドウサイズを取得
  windowSize_ = ofGetWindowSize();

  spawnPosMin_ = ofVec2f(0, ofGetWindowHeight());
  spawnPosMax_ = ofVec2f(ofGetWindowSize());

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
    float px = ofRandom(spawnPosMin_.x, spawnPosMax_.x);
    float py = ofRandom(spawnPosMin_.y, spawnPosMax_.y);
    float vx = ofRandom(velocityMin_.x, velocityMax_.x);
    float vy = ofRandom(velocityMin_.y, velocityMax_.y);
    
    ofVec3f pos(px, py, 0);
    ofVec3f vel(vx, vy, 0);
  
    stars_.emplace_back(
      make_unique<Star>(
        pos,
        vel,
        starColor_,
        ofRandom(extendMin_, extendMax_), ///< 時間経過で伸びる速度(height)
        0.07,                             ///< 時間経過で縮む速度(width)
        0.13f,                            ///< heightに対して節目がどこにあるか(0~1)
        ofRandom(widthMin_, widthMax_),   ///< width
        ofRandom(heightMin_, heightMax_)  ///< height
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
  // deltaTime * 60 = 1;
  float sync = deltaTime * ofGetFrameRate();
  
  pos_    += vel_    * sync;
  height_ += extend_ * sync;
  width_  -= shrink_ * sync;
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













