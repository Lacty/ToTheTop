
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
  gravity_          = playerJson["Gravity"].asFloat();
  jumpPow_          = playerJson["JumpPow"].asFloat();
  moveSpeed_        = playerJson["MoveSpeed"].asFloat();
  round_            = playerJson["Round"].asFloat();
  teleportCoolTime_ = playerJson["TeleportCoolTime"].asFloat();
  productionTime_   = playerJson["ProductionTime"].asFloat();

  // 画面分割数からPlayerのサイズを変更
  ofxJSON brickJson;
  brickJson.open("Actor/brickManager.json");
  column_ = brickJson["Column"].asInt();
  p_size_ = (ofGetWindowWidth() / column_) * 0.6f;

  // Playerの画像読み込み(上下が逆さまだったのでmirror関数で反転)
  tex_.load("Texture/normal2.png");
  tex_.mirror(true, false);
  texColor_   = ofColor::white;
  cdTexColor_ = ofColor::black;

  // 名前とサイズを設定
  name_          = "Player";
  tag_           = PLAYER;
  color_         = ofFloatColor::black;
  cdRectColor_   = ofFloatColor::white;
  pos_           = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
  size_          = ofVec2f(p_size_, p_size_);
  vel_           = ofVec2f(0.0f, 0.0f);
  addVelocity_   = true;
  canControl_    = true;
  canTeleport_   = true;
  isTeleporting_ = false;
  teleportTimer_ = 0.0f;
  elapsedProductionTime_ = 0.0f;

  setupColorAnim();

  // アニメーション設定
  curveX_ = AnimCurve(playerJson["DefaultAnimCurveX"].asInt());
  animX_.animateFromTo(size_.x, size_.x);
  animX_.setDuration(1);
  animX_.setRepeatType(LOOP_BACK_AND_FORTH);
  animX_.setCurve(curveX_);

  curveY_ = AnimCurve(playerJson["DefaultAnimCurveY"].asInt());
  animY_.animateFromTo((size_.y / 10) * 11, size_.y);
  animY_.setDuration(0.6);
  animY_.setRepeatType(LOOP_BACK_AND_FORTH);
  animY_.setCurve(curveY_);

  joy_.setup(GLFW_JOYSTICK_1);
  stateMgr_ = make_shared<StateManager>();
}

void Player::setup() {
  // 初期状態を設定
  // 立ち状態を追加
  stateMgr_->add(make_shared<StandingState>(), this);

  enableCollision();
  enableUpdate();
}

void Player::update(float deltaTime) {
  stateMgr_->update(deltaTime, this, stateMgr_.get(), joy_);

  float sync = deltaTime * ofGetFrameRate();

  // 落下速度の制御
  if (vel_.y <= -jumpPow_) { vel_.y = -jumpPow_; }
  else{ vel_.y -= gravity_ * sync; }
  
  // 加速度を加える判定がtrueの時に移動(重力加速度含む)
  if (addVelocity_) {
    pos_    += vel_ * sync;
  }
  animX_.update(deltaTime);
  animY_.update(deltaTime);
  onFloor_ = false;

  teleportTimer(sync);
  teleportingEffect(sync);
}

void Player::draw() {
  stateMgr_->draw(this);

  // 四角の表示
  ofPushStyle();
  ofPushMatrix();
  ofSetColor(color_);
  ofTranslate(ofVec2f(pos_.x + size_.x/2, pos_.y));
  ofScale(ofVec2f(size_.x / (float)animX_, size_.y/(float)animY_));
  ofDrawRectRounded(ofVec2f(-size_.x/2, 0.0f), size_.x, size_.y, round_);
  ofPopMatrix();
  ofPopStyle();

  // 顔文字の表示
  ofPushMatrix();
  ofPushStyle();
  ofSetColor(texColor_);
  ofTranslate(ofVec2f(pos_.x + size_.x / 2, pos_.y));
  ofScale(ofVec2f(size_.x / (float)animX_, size_.y / (float)animY_));
  tex_.draw(ofVec2f(-size_.x / 2, 0.0f),size_.x, size_.y);
  ofPopStyle();
  ofPopMatrix();
}

void Player::onCollision(Actor* c_actor) {
  stateMgr_->onCollision(this, c_actor);
}

void Player::gui() {
  if (ImGui::BeginMenu("Player_State")) {
    ImGui::SliderFloat("Size", &p_size_, 50.0f, 100.0f);
    ImGui::SliderFloat("Gravity"  , &gravity_  , 0.0f, 3.0f);
    ImGui::SliderFloat("JumpPow"  , &jumpPow_  , 0.5f, 30.0f);
    ImGui::SliderFloat("MoveSpeed", &moveSpeed_, 1.0f, 10.0f);
    ImGui::SliderFloat("ProductionTime", &productionTime_, 0.1f, 1.0f);
    ImGui::SliderInt("CoolTime", &teleportCoolTime_, 1, 10);

    ImGui::SliderFloat("Round", &round_, 0.0f, 40.0f);
    ImGui::ColorEdit3("Rect Color", &color_.r);
    ImGui::ColorEdit3("CD Rect Color", &cdRectColor_.r);

    ImGui::ColorEdit3("Face Color", &texColor_.r);
    ImGui::ColorEdit3("CD Face Color", &cdTexColor_.r);
    ImGui::EndMenu();
  }
}

// スキルの再使用時間処理
void Player::teleportTimer(float sync) {
  if (!canTeleport_ && !isTeleporting_) {
    updateColorAnim(sync);
    teleportTimer_ += sync;
  }
  if (teleportTimer_ >= teleportCoolTime_ * ofGetFrameRate()) {
    canTeleport_   = true;
    teleportTimer_ = 0.0f;
  }
}

void Player::teleportingEffect(float sync) {
  // テレポート中の処理
  if (isTeleporting_) {
    elapsedProductionTime_ += sync;

    // 演出所要時間の半数で演出を区切る
    if (elapsedProductionTime_ <= (productionTime_ * ofGetFrameRate()) / 2) {
      /*移動前の座標でプレイヤーが徐々に小さくなる*/
      size_ -= (p_size_ / productionTime_ / ofGetFrameRate()) * 2;
      beforePos_ += (p_size_ / productionTime_ / ofGetFrameRate());
      pos_ = beforePos_;
    }

    if (elapsedProductionTime_ > (productionTime_ * ofGetFrameRate()) / 2 &&
        elapsedProductionTime_ <= (productionTime_ * ofGetFrameRate())) {
      /*移動先でプレイヤーが徐々に大きくなる*/
      size_ += (p_size_ / productionTime_ / ofGetFrameRate()) * 2;
      afterPos_ -= (p_size_ / productionTime_ / ofGetFrameRate());
      pos_ = afterPos_ + p_size_/2;
    }

    // 演出所要時間を越えたら終了
    if (elapsedProductionTime_ > productionTime_ * ofGetFrameRate()) {
      isTeleporting_ = false;
      size_ = ofVec2f(p_size_, p_size_);
      elapsedProductionTime_ = 0;
    }
  }
}

void Player::setupColorAnim() {
  rectR_.setDuration(1);
  rectR_.setRepeatType(PLAY_ONCE);
  rectR_.setCurve(LINEAR);

  rectG_.setDuration(1);
  rectG_.setRepeatType(PLAY_ONCE);
  rectG_.setCurve(LINEAR);

  rectB_.setDuration(1);
  rectB_.setRepeatType(PLAY_ONCE);
  rectB_.setCurve(LINEAR);

  texR_.setDuration(1);
  texR_.setRepeatType(PLAY_ONCE);
  texR_.setCurve(LINEAR);

  texG_.setDuration(1);
  texG_.setRepeatType(PLAY_ONCE);
  texG_.setCurve(LINEAR);

  texB_.setDuration(1);
  texB_.setRepeatType(PLAY_ONCE);
  texB_.setCurve(LINEAR);
}

void Player::setColorAnimFromTo() {
  rectR_.animateFromTo(cdRectColor_.r, color_.r);
  rectG_.animateFromTo(cdRectColor_.g, color_.g);
  rectB_.animateFromTo(cdRectColor_.b, color_.b);

  texR_.animateFromTo(cdTexColor_.r, texColor_.r);
  texG_.animateFromTo(cdTexColor_.g, texColor_.g);
  texB_.animateFromTo(cdTexColor_.b, texColor_.b);
}

void Player::updateColorAnim(float sync) {
  rectR_.update((sync / ofGetFrameRate()) / teleportCoolTime_);
  color_.r = rectR_;

  rectG_.update(sync / ofGetFrameRate() / teleportCoolTime_);
  color_.g = rectG_;

  rectB_.update(sync / ofGetFrameRate() / teleportCoolTime_);
  color_.b = rectB_;


  texR_.update(sync / ofGetFrameRate() / teleportCoolTime_);
  texColor_.r = texR_;

  texG_.update(sync / ofGetFrameRate() / teleportCoolTime_);
  texColor_.g = texG_;

  texB_.update(sync / ofGetFrameRate() / teleportCoolTime_);
  texColor_.b = texB_;
}
