
/**
* @file   teleportCursor.h
* @brief  �e���|�[�g�J�[�\��(�ړ���\��)
*
* @author wem
* @date   2016.1.6
*/

#include "precompiled.h"


TeleportCursor::TeleportCursor() {
  // Json�t�@�C������K�v�Ȑ��l�̓ǂݍ���
  ofxJSON json;
  json.open("Actor/teleportCursor.json");
  moveSpeed_ = json["MoveSpeed"].asFloat();
  reduce_    = json["Reduce"].asFloat();
  circle_    = json["Circle"].asFloat();

  // ���O�ƃT�C�Y��ݒ�
  name_  = "TeleportCursor";
  tag_   = TELEPORT_CURSOR;
  color_ = ofFloatColor::white;
}

void TeleportCursor::setup() {
  enableCollision();
  enableUpdate();
}

void TeleportCursor::update(float deltaTime) {
  // Brick�ɂԂ����Ă�����ԁA�Ԃ����ĂȂ���Δ��ɕϐF
  if (onBrick_) { color_ = ofFloatColor::red; }
  else { color_ = ofFloatColor::white; }

  // �J�[�\���̈ړ�����
  float sync = g_local->LastFrame() * ofGetFrameRate();
  pos_ += vel_ * sync;

  // �J�[�\�����v���C���[�̓����ɉ����ĉ�ʊO�Ɉړ�����̂�h��
  sync = deltaTime * ofGetFrameRate();
  pos_.y += playerVel_.y * sync;
  if (pos_.x > 0 && pos_.x + size_.x < ofGetWidth()) {
    pos_.x += playerVel_.x * sync;
  }

  onBrick_ = false;
}

void TeleportCursor::draw() {
  // �X�L���̗L���͈͂�Playe�̒��S����~�ŕ\��
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawCircle((playerPos_ + (size_ / 2)), circle_);
  ofPopMatrix();
  ofPopStyle();

  // �J�[�\���̕`��
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), round_);
  ofPopMatrix();
  ofPopStyle();
}

void TeleportCursor::onCollision(Actor* c_actor) {
  // Brick�Ƃ̏Փ˔���
  if (c_actor->getTag() == BRICK) { onBrick_ = true; }
}

void TeleportCursor::gui() {
  if (ImGui::BeginMenu("Teleport_Param")) {
    ImGui::SliderFloat("Reduce", &reduce_, 0.1f, 1.0f);
    ImGui::SliderFloat("Round", &round_, 0.0f, 40.0f);
    ImGui::SliderFloat("CursorSpeed", &moveSpeed_, 1.0f, 10.0f);
    ImGui::SliderFloat("Circle", &circle_, 100.0f, 500.0f);
    ImGui::EndMenu();
  }
}
