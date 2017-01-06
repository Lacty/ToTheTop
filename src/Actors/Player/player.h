
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

  ofImage tex_;                       ///< プレイヤーの画像
  ofFloatColor texColor_;             ///< 顔文字部分の色

  bool  onFloor_;                     ///< Brickの上に居るかを判定
  bool  isDead_;                      ///< Brickに挟まれ死亡したかどうかの判定
  float gravity_;                     ///< 重力
  float jumpPow_;                     ///< ジャンプ力
  float moveSpeed_;                   ///< 移動速度
  
  float round_;                       ///< プレイヤーの丸み
  int   column_;                      ///< Brickの列数をサイズの算出に利用

  bool  canTeleport_;                 ///< テレポートが使用可能か判定
  int   teleportCoolTime_;            ///< テレポート再使用までの待ち時間
  float teleportTimer_;               ///< テレポート使用直後から計測するタイマー

  float reduce_;                      ///< Teleport使用中のスロー倍率
  float cursorSpeed_;                 ///< TeleportCursorの移動速度
  float teleportCircle_;              ///< テレポートの有効範囲を示した円のサイズ

  void teleportTimer(float sync);

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

  bool  getCanTeleport() const;
  void  setCanTeleport(bool c);

  float getReduce() const;
  float getCursorSpeed() const;
  float getTeleportCircle() const;

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

inline bool  Player::getCanTeleport() const       { return canTeleport_; }
inline void  Player::setCanTeleport(bool c)       { canTeleport_ = c; }

inline float Player::getReduce() const            { return reduce_; }
inline float Player::getCursorSpeed() const       { return cursorSpeed_; }
inline float Player::getTeleportCircle() const    { return teleportCircle_; }
