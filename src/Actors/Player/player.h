
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

  void pullBrick(Actor* c_actor); // CollisionしたBrickを引っ張る
  void actorSearch(Actor* c_actor); // 左右にenableCollision()したActorがないか判定
public:
  Player();

  // 衝突したActorの方向判定用(両側にActorがあった場合を想定)
  bool isHitLeft_;
  bool isHitRight_;

  void setup() override;
  void update(float deltaTime) override;
  void draw() override;

  void onCollision(Actor* c_actor) override;

};
