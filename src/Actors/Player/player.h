
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

  float gravity_;                     ///< 重力
  float jumpPow_;                  ///< ジャンプ力
  float moveSpeed_;                   ///< 移動速度

  void gui();
public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  
  float getJumpPow();
  void  setJumpPow(float newJumpPow);
  float getGravity();
  float getMoveSpeed();

  void  onCollision(Actor* c_actor) override;
  bool  onFloor();                     ///< 地面の上に居るかを判定  
};

inline float Player::getJumpPow()   { return jumpingPow_; }
inline void  Player::setJumpPow(float newJP) { jumpPow_ = newJP; }

inline float Player::getGravity()   { return gravity_; }
inline float Player::getMoveSpeed() { return moveSpeed_; }
