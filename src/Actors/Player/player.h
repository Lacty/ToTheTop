
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

  void gui();
public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  
  bool  getOnFloor() const;
  void  setOnFloor(bool truth);
  float getJumpPow();
  void  setJumpPow(float newJumpPow);
  float getGravity();
  float getMoveSpeed();

  void  onCollision(Actor* c_actor) override;
};

inline bool  Player::getOnFloor() const           { return onFloor_; }
inline void  Player::setOnFloor(bool truth)       { onFloor_ = truth; }

inline float Player::getJumpPow()                 { return jumpPow_; }
inline void  Player::setJumpPow(float newJumpPow) { jumpPow_ = newJumpPow; }

inline float Player::getGravity()                 { return gravity_; }
inline float Player::getMoveSpeed()               { return moveSpeed_; }
