
/**
 * @file   gameLocal.cpp
 * @brief  共通で使用するものを置いている
 *
 * @author y.akria
 * @date   2017.01.02
 */

#include "precompiled.h"


// -----------------------------------------------------------
unique_ptr<GameLocal> g_local = make_unique<GameLocal>();


GameLocal::GameLocal()
  : width_    ( 0 )
  , height_   ( 0 )
  , lastFrame_( 0 )
  , frameAcc_ ( 0 )
{}

void GameLocal::Setup() {
  ofxJSON json;
  json.open("game.json");
  
  frameAcc_ = json["acceleration"].asFloat();
  
  width_  = ofGetWidth();
  height_ = ofGetHeight();
  
  ofAddListener(ofEvents().update,        this, &GameLocal::update);
  ofAddListener(ofEvents().windowResized, this, &GameLocal::windowResized);
}

void GameLocal::update(ofEventArgs &args) {
  lastFrame_ = ofGetLastFrameTime();
}

void GameLocal::windowResized(ofResizeEventArgs &resize) {
  width_  = resize.width;
  height_ = resize.height;
}

int GameLocal::Width()  const { return width_;  }
int GameLocal::Height() const { return height_; }

int GameLocal::HalfWidth()  const { return int(width_  * 0.5f); }
int GameLocal::HalfHeight() const { return int(height_ * 0.5f); }

ofVec2f GameLocal::WindowSize()     const { return ofVec2f(width_, height_); }
ofVec2f GameLocal::WindowHalfSize() const { return ofVec2f(width_ * 0.5f, height_ * 0.5f); }

float GameLocal::LastFrame() const      { return lastFrame_; }
float GameLocal::AccedLastFrame() const { return lastFrame_ * frameAcc_; }
float GameLocal::FrameAcc()  const      { return frameAcc_;  }

void GameLocal::SetFrameAcc(float acc) {
  frameAcc_ = acc;
}
