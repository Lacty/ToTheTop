
/**
 * @file   playerState.h
 * @brief  プレイヤーの状態
 *
 * @author y.akira
 * @date   2016.12.17
 */

#pragma once


/**
 * @enum プレイヤーの状態
 */
enum PlayerState {
  STANDING = 0 ///< 立ち状態
};

//! 状態クラス(立ち)
class StandingState : public StateBase {
public:
  // タグを設定
  StandingState() { tag_ = STANDING; }
  virtual ~StandingState() {}
  
  virtual void setup(Player* player) override;
  virtual void handleInput(Player* player, ofxJoystick& input) override;
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) override;
  virtual void draw(Player* player) override;
  
};
