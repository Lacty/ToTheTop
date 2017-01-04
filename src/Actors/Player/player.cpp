
/**
 * @file   player.h
 * @brief  プレイヤー
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


Player::Player() {
  ofxJSON playerJson;
  playerJson.open("Actor/player.json");
  round_          = playerJson["Round"].asFloat();
  gravity_        = playerJson["Gravity"].asFloat();
  jumpPow_        = playerJson["JumpPow"].asFloat();
  moveSpeed_      = playerJson["MoveSpeed"].asFloat();
  reduce_         = playerJson["Reduce"].asFloat();
  cursorSpeed_    = playerJson["CursorSpeed"].asFloat();
  teleportCircle_ = playerJson["TeleportCircle"].asFloat();

  // 画面分割数からPlayerのサイズを変更
  ofxJSON brickJson;
  brickJson.open("Actor/brickManager.json");
  column_ = brickJson["Column"].asInt();
  float p_size = (ofGetWindowWidth() / column_) * 0.8f;

  // Playerの画像読み込み(上下が逆さまだったのでmirror関数で反転)
  tex_.load("Texture/normal2.png");
  tex_.mirror(true, false);
  texColor_ = ofColor::white;

  // 名前とサイズを設定
  name_ = "Player";
  tag_  = PLAYER;
  color_ = ofFloatColor::black;
  pos_  = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
  size_ = ofVec2f(p_size, p_size);
  vel_  = ofVec2f(0.0f, 0.0f);

  joy_.setup(GLFW_JOYSTICK_1);
  stateMgr_ = make_shared<StateManager>();
}

void Player::setup() {
  // 初期状態を設定
  // 立ち状態を追加
  stateMgr_->add(make_shared<StandingState>(), this);

  // 次の状態へ移行
  // stateMgr_->push();

  // しゃがみ状態を追加
  //stateMgr_->add(make_shared<DuckingState>(), this);

  // 前の状態にもどる
  // stateMgr_->pop();

  enableCollision();
  enableUpdate();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);

  float sync = deltaTime * ofGetFrameRate();

  // 落下速度の制御
  if (vel_.y <= -jumpPow_) { vel_.y = -jumpPow_; }
  else{ vel_.y -= gravity_ * sync; }
  
  pos_    += vel_ * sync;
  onFloor_ = false;
}

void Player::draw() {
  stateMgr_->draw(this);

  ofPushStyle();
  ofSetColor(color_);
  ofDrawRectRounded(getRectangle(), round_);
  ofPopStyle();

  ofPushStyle();
  ofSetColor(texColor_);
  tex_.draw(pos_.x, pos_.y,size_.x, size_.y);
  ofPopStyle();

}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);
}

void Player::gui() {
  if (ImGui::BeginMenu("Player_State")) {
    ImGui::SliderFloat("Gravity"  , &gravity_  , 0.0f, 3.0f);
    ImGui::SliderFloat("JumpPow"  , &jumpPow_  , 0.5f, 30.0f);
    ImGui::SliderFloat("MoveSpeed", &moveSpeed_, 1.0f, 10.0f);

    ImGui::SliderFloat("Round", &round_, 0.0f, 40.0f);
    ImGui::ColorEdit3("Rect Color", &color_.r);
    ImGui::ColorEdit3("Face Color", &texColor_.r);
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Teleport_Param")) {
    ImGui::SliderFloat("Reduce", &reduce_, 0.1f, 1.0f);
    ImGui::SliderFloat("CursorSpeed", &cursorSpeed_, 1.0f, 10.0f);
    ImGui::SliderFloat("Circle", &teleportCircle_, 100.0f, 500.0f);
    ImGui::EndMenu();
  }
}
