﻿
/**
 * @file   stateManager.h
 * @brief  Actorの状態を管理するクラス
 *
 * @author y.akira
 * @date   2016.12.17
 */

#pragma once
#include <array>
#include <forward_list>

class StateBase;

//! 状態マネージャー
class StateManager {
private:
  static constexpr std::size_t MAX_STACK = 10; ///< 管理する状態の最大数(スタック)
  
  using p_state = shared_ptr<StateBase>;
  
  std::array<std::forward_list<p_state>, MAX_STACK> states_; ///< 状態リスト
  std::size_t                   index_;  ///< 操作中のスタックの配列数
  
public:
  StateManager();
  ~StateManager() {}
  
  void update(float deltaTime,
              Player* player,
              StateManager* stateMgr,
              ofxJoystick& input);            ///< スタックされた現在の状態のupdateを呼ぶ
  
  void draw(Player* player);                  ///< スタックされた現在の状態のdrawを呼ぶ
  
  void onCollision(Player* player,
                   Actor*  c_actor);          ///< スタックされた現在のonCollisionを呼ぶ
  
  void push();                                ///< スタックを次に進める
  void pop();                                 ///< スタックを前に戻す
  
  void add(const p_state& state, Player* player); ///< 状態を追加する
  void remove(const int tag);                     ///< 特定の状態を削除する
};
