
/**
 * @file   playerState.h
 * @brief  プレイヤーの状態
 *
 * @author y.akira
 * @date   2016.12.17
 */

#pragma once


/**
 * @enum プレイヤーの状態
 */
enum PlayerState {
  STANDING = 0, ///< 立ち
  DUCKING,      ///< しゃがみ
  MOVING,       ///< 移動
  JUMPING,      ///< ジャンプ
  TELEPORT,     ///< テレポート(スキル)
};


/**
 * @brief 状態の基底クラス
 */
class StateBase {
protected:
  int tag_;
  
public:
  StateBase()
    : tag_(-1)
  {}
  
  ~StateBase() {}
  
  // 起動後に一度呼ばれます
  virtual void setup(Player* player);
  
  // 入力により状態を変更するために毎フレーム呼ばれます
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input);
  
  // 毎フレーム呼ばれます
  virtual void update(float deltaTime, Player* player, ofxJoystick& input);
  
  // 描画用に毎フレーム呼ばれます
  virtual void draw(Player* player);
  
  // プレイヤーが別のアクターと衝突した際に呼ばれます
  virtual void onCollision(Player* player, Actor* c_actor);
  
  //! タグを返します
  int getTag() const { return tag_; }
};


//! 状態クラス(立ち)
class StandingState : public StateBase {
public:
  // タグを設定
  StandingState() { tag_ = STANDING; }
  virtual ~StandingState() {}
  
  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
  virtual void onCollision(Player* player, Actor* c_actor) override;
};


//! 状態クラス(しゃがみ)
class DuckingState : public StateBase {
public:
  // タグを設定
  DuckingState() { tag_ = DUCKING; }
  virtual ~DuckingState() {}

  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
};


//! 状態クラス(移動)
class MovingState : public StateBase {
public:
  // タグを設定
  MovingState() { tag_ = MOVING; }
  virtual ~MovingState() {}

  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
  virtual void onCollision(Player* player, Actor* c_actor) override;
};


//! 状態クラス(ジャンプ)
class JumpingState : public StateBase {
public:
  // タグを設定
  JumpingState() { tag_ = JUMPING; }
  virtual ~JumpingState() {}

  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
};


//! 状態クラス(テレポート)
class TeleportState : public StateBase {
private:
  float   currentAcc_;  ///< Teleportスキル使用前のフレームレートを一時保存
  ofVec2f cursorPos_;   ///< 移動先カーソルのポジション
  ofVec2f cursorSize_;  ///< 移動先カーソルのサイズ
  ofVec2f cursorVel_;   ///< 移動先カーソルの加速度

  void moveTelePos(Player* player, ofxJoystick& input); ///< マーカー移動処理
public:
  // タグを設定
  TeleportState() { tag_ = TELEPORT; }
  virtual ~TeleportState() {}

  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
  virtual void onCollision(Player* player, Actor* c_actor) override;
};
