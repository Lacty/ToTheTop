
/**
* @file   teleportCursor.h
* @brief  テレポートカーソル(移動先表示)
*
* @author wem
* @date   2016.1.6
*/

#pragma once


//! @brief テレポートカーソルクラス
class TeleportCursor : public Actor {
private:
  int w_, h_;             ///< デフォルトの画面サイズを保存
  float wRatio_, hRatio_; ///< 変更前後の画面倍率

  bool    onBrick_;       ///< Brickとの衝突判定
  float   moveSpeed_;     ///< 移動速度
  float   reduce_;        ///< Teleport使用中のスロー倍率
  float   circle_;        ///< テレポートの有効範囲を示した円のサイズ

  float   round_;         ///< カーソルの丸み
  ofVec2f playerPos_;     ///< プレイヤーの現在地を一時保存
  ofVec2f playerVel_;     ///< プレイヤーの移動量を一時保存

public:
  TeleportCursor();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  void  gui()  override;

  void  setRound(float round);
  void  setPlayerPos(ofVec2f p_pos);
  void  setPlayerVel(ofVec2f p_vel);

  bool  onBrick()    const;
  float getSpeed()   const;
  float getReduce()  const;
  float getCircle()  const;

  void  onCollision(Actor* c_actor) override;
};

inline void  TeleportCursor::setRound(float r)           { round_ = r; }
inline void  TeleportCursor::setPlayerPos(ofVec2f p_pos) { playerPos_ = p_pos; }
inline void  TeleportCursor::setPlayerVel(ofVec2f p_vel) { playerVel_ = p_vel; }

inline bool  TeleportCursor::onBrick()    const          { return onBrick_; }
inline float TeleportCursor::getSpeed()   const          { return moveSpeed_; }
inline float TeleportCursor::getReduce()  const          { return reduce_; }
inline float TeleportCursor::getCircle()  const          { return circle_; }

