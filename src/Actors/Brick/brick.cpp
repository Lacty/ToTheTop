
#include "precompiled.h"


Brick::Brick() {
  // ���O�ƃT�C�Y��ݒ�
  name_ = "Brick";
  pos_ = ofVec2f(0, 0);
  size_ = ofVec2f(30, 30);
}

void Brick::setup() {
  // �摜�̃��[�h
  brickImg_.load("textures/brick.jpg");

  enableUpdate();
  enableCollision();
}

void Brick::update(float deltaTime) {}

void Brick::draw() {
  ofSetColor(ofColor::white);
  brickImg_.draw(pos_);
}

void Brick::onCollision(Actor* c_actor) {}
