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
  ofxJoystick              joy_;      ///< ゲームパッドの入力判定をとる
  shared_ptr<StateManager> stateMgr_; ///< プレイヤーの状態を管理する

  ofImage      tex_;                  ///< プレイヤーの画像
  ofFloatColor texColor_;             ///< 顔文字部分の色

  ofxAnimatableFloat animX_, animY_;  ///< アニメーション用変数(x, y)

  bool    canControl_;                ///< コントローラーからの命令を受け付けるか
  bool    onFloor_;                   ///< Brickの上に居るかを判定
  bool    isDead_;                    ///< Brickに挟まれ死亡したかどうかの判定
  float   gravity_;                   ///< 重力
  float   jumpPow_;                   ///< ジャンプ力
  float   moveSpeed_;                 ///< 移動速度
  
  float   round_;                     ///< プレイヤーの丸み
  int     column_;                    ///< Brickの列数をサイズの算出に利用

  bool    canTeleport_;               ///< テレポートが使用可能か判定
  int     teleportCoolTime_;          ///< テレポート再使用までの待ち時間
  float   teleportTimer_;             ///< テレポート使用直後から計測するタイマー

  float   p_size_;                    ///< プレイヤーサイズの保管
  bool    isTeleporting_;             ///< テレポート中か判定
  ofVec2f beforePos_;                 ///< テレポート前の座標を一時保存  
  ofVec2f afterPos_;                  ///< テレポート後の座標を一時保存  
  float   elapsedProductionTime_;     ///< 演出経過時間
  float   productionTime_;            ///< 演出所要時間

  void teleportTimer(float sync);
  void teleportingEffect(float sync);
public:
  Player();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  void  gui()  override;

  bool  onFloor() const;
  void  onFloor(bool f);
  bool  isDead() const;
  void  isDead(bool d);
  float getJumpPow() const;
  void  setJumpPow(float newJumpPow);
  float getGravity() const;
  float getMoveSpeed() const;
  float getRound() const;

  bool  canTeleport() const;
  void  canTeleport(bool c);

  bool  isTeleporting() const;
  void  isTeleporting(bool i);
  void  setBeforePos(ofVec2f before);
  void  setAfterPos(ofVec2f after);

  void  onCollision(Actor* c_actor) override;
};

inline bool  Player::onFloor() const              { return onFloor_; }
inline void  Player::onFloor(bool f)              { onFloor_ = f; }

inline bool  Player::isDead() const               { return isDead_; }
inline void  Player::isDead(bool d)               { isDead_ = d; }

inline float Player::getJumpPow() const           { return jumpPow_; }
inline void  Player::setJumpPow(float newJumpPow) { jumpPow_ = newJumpPow; }

inline float Player::getGravity() const           { return gravity_; }
inline float Player::getMoveSpeed() const         { return moveSpeed_; }

inline float Player::getRound() const             { return round_; }

inline bool  Player::canTeleport() const          { return canTeleport_; }
inline void  Player::canTeleport(bool c)          { canTeleport_ = c; }

inline bool  Player::isTeleporting() const        { return isTeleporting_; }
inline void  Player::isTeleporting(bool c)        { isTeleporting_ = c; }

inline void Player::setBeforePos(ofVec2f before)  { beforePos_ = before; }
inline void Player::setAfterPos(ofVec2f after)    { afterPos_ = after; }
