﻿
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
  ofxJoystick              joy_; ///< ゲームパッドの入力判定をとる
  shared_ptr<StateManager> mgr_; ///< プレイヤーの状態を管理する
  
public:
  Player();
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void onCollisionEnter(Actor& c_actor) override;
  
  
  void Piy() { ofLog() << "player say \"Piy\""; };
};
