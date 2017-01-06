
/**
* @file   player.h
* @brief  �v���C���[
*
* @author y.akira
* @date   2016.12.14
*/

#include "precompiled.h"


TeleportCursor::TeleportCursor()
  :onBrick_(false)
{
  // Json�t�@�C������K�v�Ȑ��l�̓ǂݍ���
  ofxJSON cursorJson;
  cursorJson.open("Actor/teleportCursor.json");
  moveSpeed_ = cursorJson["MoveSpeed"].asFloat();
  reduce_    = cursorJson["Reduce"].asFloat();
  circle_    = cursorJson["TeleportCircle"].asFloat();

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

  onBrick_ = false;

  float sync = g_local->LastFrame() * ofGetFrameRate();
  pos_ += vel_ * sync;

  // �J�[�\�����v���C���[�̓����ɉ����ĉ�ʊO�Ɉړ�����̂�h��
  float sync = deltaTime * ofGetFrameRate();
  pos_.y += playerVel_.y * sync;
  if (pos_.x > 0 && pos_.x + size_.x < ofGetWidth()) {
    pos_.x += playerVel_.x * sync;
  }

  movePos(joy_);
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

// �J�[�\���̈ړ�����
void TeleportCursor::movePos(ofxJoystick& input) {
  // �J�[�\���ƃv���C���[�̒��S���W
  ofVec2f c_center = ofVec2f(pos_.x + (size_.x / 2),
                             pos_.y + size_.y);
  ofVec2f p_center = playerPos_ + (size_ / 2);

  // ���E�ւ̈ړ�
  if (input.isPushing(Input::Left) &&
      pos_.x >= 0 &&
      p_center.distance(c_center - ofVec2f(moveSpeed_, 0.0f)) <= circle_) {
    vel_.x = -moveSpeed_;
  }
  else if (input.isPushing(Input::Right) &&
           pos_.x + size_.x <= ofGetWidth() &&
           p_center.distance(c_center + ofVec2f(moveSpeed_, 0.0f)) <= circle_) {
    vel_.x = moveSpeed_;
  }
  else {
    vel_.x = 0.0f;
  }

  // �㉺�ւ̈ړ�
  if (input.isPushing(Input::Down) &&
      p_center.distance(c_center - ofVec2f(0.0f, moveSpeed_)) <= circle_) {
    vel_.y = -moveSpeed_;
  }
  else if (input.isPushing(Input::Up) &&
           p_center.distance(c_center + ofVec2f(0.0f, moveSpeed_)) <= circle_) {
    vel_.y = moveSpeed_;
  }
  else {
    vel_.y = 0.0f;
  }
}