
/**
* @file   teleportCursor.h
* @brief  テレポートカーソル(移動先表示)
*
* @author wem
* @date   2016.1.6
*/

#include "precompiled.h"


TeleportCursor::TeleportCursor() {
  // jsonから設定を読み込む
  ofxJSON json;
  json.open("user.json");
  w_ = json["Window"]["width"].asInt();
  h_ = json["Window"]["height"].asInt();

  // Jsonファイルから必要な数値の読み込み
  ofxJSON teleportJson;
  teleportJson.open("Actor/teleportCursor.json");
  moveSpeed_ = teleportJson["MoveSpeed"].asFloat();
  reduce_    = teleportJson["Reduce"].asFloat();
  circle_    = teleportJson["Circle"].asFloat();

  // 名前とサイズを設定
  name_  = "TeleportCursor";
  tag_   = TELEPORT_CURSOR;
  color_ = ofFloatColor::white;

  wRatio_ = ofGetWidth() / (float)w_;
  hRatio_ = ofGetHeight() / (float)h_;
  moveSpeed_ = moveSpeed_ * hRatio_;
  circle_ = circle_ * hRatio_;
}

void TeleportCursor::setup() {
  enableCollision();
  enableUpdate();
}

void TeleportCursor::update(float deltaTime) {
  // Brickにぶつかっていたら赤、ぶつかってなければ白に変色
  if (onBrick_) { color_ = ofFloatColor::red; }
  else { color_ = ofFloatColor::white; }

  // カーソルの移動処理
  float sync = g_local->LastFrame() * ofGetFrameRate();
  pos_ += vel_ * sync;

  // カーソルがプレイヤーの動きに応じて画面外に移動するのを防ぐ
  sync = deltaTime * ofGetFrameRate();
  pos_.y += playerVel_.y * sync;
  if (pos_.x > 0 && pos_.x + size_.x < ofGetWidth()) {
    pos_.x += playerVel_.x * sync;
  }

  onBrick_ = false;
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
