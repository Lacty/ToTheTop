
/**
 * @file     backGround.cpp
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#include "precompiled.h"


BackGround::BackGround()
  : interval_ ( 0 )
  , deltaTime_( 0 )
  , widthMin_ ( 0 )
  , widthMax_ ( 0 )
  , heightMin_( 0 )
  , heightMax_( 0 )
  , extendMin_( 0 )
  , extendMax_( 0 )
{}

void BackGround::windowResizeCallback(ofResizeEventArgs &resize) {
  windowSize_.x = resize.width;
  windowSize_.y = resize.height;
}

void BackGround::gui() {
  if (ImGui::BeginMenu("BackGround")) {
  
    string str = "Start Num :" + ofToString(stars_.size());
    ImGui::Text("%s", str.c_str());
  
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
  
    ImGui::EndMenu();
  }
}

void BackGround::setup() {
  // 現在のウィンドウサイズを取得
  windowSize_ = ofGetWindowSize();
  
  string path = "BackGround/backGround.json";
  ofxJSON json;
  if (json.open(path.c_str())) {
    ofLog() << "\"" << path.c_str() << "\"" << " loaded";
    
    interval_ = json["interval"].asFloat();
    widthMin_ = json["Width"]["min"].asFloat();
    widthMax_ = json["Width"]["max"].asFloat();
    heightMin_ = json["Height"]["min"].asFloat();
    heightMax_ = json["Height"]["max"].asFloat();
    extendMin_ = json["Extend"]["min"].asFloat();
    extendMax_ = json["Extend"]["max"].asFloat();
    for (int i = 0; i < 2; i++) {
      velocityMin_[i] = json["Velocity"]["min"][i].asFloat();
      velocityMax_[i] = json["Velocity"]["max"][i].asFloat();
    }
    for (int i = 0; i < 4; i++) {
        inColor_[i] = json["InColor"  ][i].asFloat();
       outColor_[i] = json["OutColor" ][i].asFloat();
      starColor_[i] = json["StarColor"][i].asFloat();
    }
  }

  spawnPosMin_ = ofVec2f(0, ofGetWindowHeight());
  spawnPosMax_ = ofVec2f(ofGetWindowSize());

  // Callback関数を登録
  ofAddListener(ofEvents().windowResized, this, &BackGround::windowResizeCallback);
}

void BackGround::update(float deltaTime) {
  deltaTime_ += deltaTime;
  
  // 星の処理
  for (auto& star : stars_) {
    star->update(deltaTime);
  }
  
  // インターバルが来たら星を生成
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
  
  // 画面外に出た星を削除する
  stars_.remove_if(
    [] (const unique_ptr<Star>& star)->bool {
      return star->outOfWindow();
    }
  );
}

void BackGround::draw() {
  ofBackgroundGradient(inColor_, outColor_);
  
  for (auto& star : stars_) {
    star->draw();
  }
}

/**
 * @brief Star生成時のパラメータを指定します
 * @param [in] pos    生成する位置
 * @param [in] vel    加速度
 * @param [in] color  色
 * @param [in] extend 時間経過で伸びる速度(height)
 * @param [in] shrink 時間経過で縮む速度(width)
 * @param [in] clause heightに対して節目がどこにあるか(0~1)
 * @param [in] width  横幅
 * @param [in] height 縦幅
 */
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

/**
 * @brief ウィンドウからはみ出たかどうか
 * @note  尻尾分考慮するのがめんどいので
 *        ウィンドウより一回り大きいサイズで判定をしている
 */
bool Star::outOfWindow() {
  // 尻尾があるので
  // 実際のウィンドウより一回り大きいサイズで判定を取る
  if ( (pos_.x > ofGetWindowWidth() * 2)
    || (pos_.x < -ofGetWindowWidth())
    || (pos_.y > ofGetWindowHeight() * 2)
    || (pos_.y < -ofGetWindowHeight()))
  {
    return true;
  }
  return false;
}
