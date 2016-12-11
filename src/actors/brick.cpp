
#include "precompiled.h"


void Brick::setup() {
  name_ = "Brick";

  pos_.x = 100;
  size_ = ofVec2f(20, 20);
  
  finishSetup();
  enableUpdate();
  enableCollision();
}

void Brick::update(float deltaTime) {}

void Brick::draw() {
  ofDrawRectangle(getRectangle());
}


void Brick::onCollisionEnter(Actor& c_actor) {}
