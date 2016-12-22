
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

  float repulsionPow_;                ///< 反発力
  
public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  
  float getRepulsion();
  void  setRepulsion(float newRepulsionPow);

  void  onCollision(Actor* c_actor) override;
  bool  onFloor();                     ///< 地面の上に居るかを判定  
};

inline float Player::getRepulsion() { return repulsionPow_; }
inline void  Player::setRepulsion(float newRepulsion) { repulsionPow_ = newRepulsion; }
