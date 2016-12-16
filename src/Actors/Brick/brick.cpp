
/**
* @file   brick.h
* @brief  レンガ
*
* @author y.akira
* @date   2016.12.14
*/

#include "precompiled.h"


Brick::Brick() {
  // 名前とサイズを設定
  name_ = "Brick";
  pos_ = ofVec2f(50, 0);
  size_ = ofVec2f(20, 20);
}

void Brick::setup() {

  auto listOfActor = FindActorsList("Player");
  ofLog() << "Player Num : " << listOfActor.size();
  
  //enableUpdate();
  enableCollision();
}

void Brick::update(float deltaTime) {}

void Brick::draw() {
  ofSetColor(color_);
  ofDrawRectangle(getRectangle());
}

void Brick::onCollisionEnter(Actor& c_actor) {
  ofLog() << "my name   : " << getName();
  ofLog() << "collision : " << c_actor.getName();
}
