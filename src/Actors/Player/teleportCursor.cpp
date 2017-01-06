
/**
* @file   teleportCursor.h
* @brief  テレポートカーソル(移動先表示)
*
* @author wem
* @date   2016.1.6
*/

#include "precompiled.h"


TeleportCursor::TeleportCursor() {
  // Jsonファイルから必要な数値の読み込み
  ofxJSON json;
  json.open("Actor/teleportCursor.json");
  moveSpeed_ = json["MoveSpeed"].asFloat();
  reduce_    = json["Reduce"].asFloat();
  circle_    = json["Circle"].asFloat();

  // 名前とサイズを設定
  name_  = "TeleportCursor";
  tag_   = TELEPORT_CURSOR;
  color_ = ofFloatColor::white;

  joy_.setup(GLFW_JOYSTICK_1);
}

void TeleportCursor::setup() {
  enableCollision();
  enableUpdate();
}

void TeleportCursor::update(float deltaTime) {
  // Brickにぶつかっていたら赤、ぶつかってなければ白に変色
  if (onBrick_) { color_ = ofFloatColor::red; }
  else { color_ = ofFloatColor::white; }

  onBrick_ = false;
  movePos(deltaTime, joy_);
}

void TeleportCursor::draw() {
  // スキルの有効範囲をPlayeの中心から円で表示
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawCircle((playerPos_ + (size_ / 2)), circle_);
  ofPopMatrix();
  ofPopStyle();

  // カーソルの描画
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), round_);
  ofPopMatrix();
  ofPopStyle();
}

void TeleportCursor::onCollision(Actor* c_actor) {
  // Brickとの衝突判定
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

// カーソルの移動処理
void TeleportCursor::movePos(float deltaTime, ofxJoystick& input) {
  // カーソルとプレイヤーの中心座標
  ofVec2f c_center = ofVec2f(pos_.x + (size_.x / 2),
                             pos_.y + size_.y);
  ofVec2f p_center = playerPos_ + (size_ / 2);

  // 左右への移動
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

  // 上下への移動
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

  float sync = g_local->LastFrame() * ofGetFrameRate();
  pos_ += vel_ * sync;

  // カーソルがプレイヤーの動きに応じて画面外に移動するのを防ぐ
  sync = deltaTime * ofGetFrameRate();
  pos_.y += playerVel_.y * sync;
  if (pos_.x > 0 && pos_.x + size_.x < ofGetWidth()) {
    pos_.x += playerVel_.x * sync;
  }
}
