
/**
 * @file   player.h
 * @brief  プレイヤー
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


class StateManager;

//! @brief プレイヤークラス
class Player : public Actor {
private:
  ofxJoystick              joy_;      ///< ゲームパッドの入力判定をとる
  shared_ptr<StateManager> stateMgr_; ///< プレイヤーの状態を管理する

  bool  onFloor_;                     ///< Brickの上に居るかを判定
  float gravity_;                     ///< 重力
  float jumpPow_;                     ///< ジャンプ力
  float moveSpeed_;                   ///< 移動速度
  
  int   column_;                      ///< Brickの列数をサイズの算出に利用

  float reduce_;                      ///< Teleport使用中のスロー倍率
  float cursorSpeed_;                 ///< TeleportCursorの移動速度
  float teleportCircle_;              ///< テレポートの有効範囲を示した円のサイズ

public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  void  gui()  override;

  bool  onFloor() const;
  void  onFloor(bool f);
  float getJumpPow() const;
  void  setJumpPow(float newJumpPow);
  float getGravity() const;
  float getMoveSpeed() const;
  float getReduce() const;
  float getCursorSpeed() const;
  float getTeleportCircle() const;

  void  onCollision(Actor* c_actor) override;
};

inline bool  Player::onFloor() const              { return onFloor_; }
inline void  Player::onFloor(bool f)              { onFloor_ = f; }

inline float Player::getJumpPow() const           { return jumpPow_; }
inline void  Player::setJumpPow(float newJumpPow) { jumpPow_ = newJumpPow; }

inline float Player::getGravity() const           { return gravity_; }
inline float Player::getMoveSpeed() const         { return moveSpeed_; }

inline float Player::getReduce() const            { return reduce_; }
inline float Player::getCursorSpeed() const       { return cursorSpeed_; }
inline float Player::getTeleportCircle() const    { return teleportCircle_; }
