
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
  float jumpingPow_;                  ///< ジャンプ力

  void guiDraw();
public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  
  float getJumpPow();
  void  setJumpPow(float newJumpPow);
  float getGravity();

  void  onCollision(Actor* c_actor) override;
  bool  onFloor();                     ///< 地面の上に居るかを判定  
};

inline float Player::getJumpPow() { return jumpingPow_; }
inline void  Player::setJumpPow(float newJumpPow) { jumpingPow_ = newJumpPow; }

inline float Player::getGravity() { return gravity_; }
