
/**
 * @file   stateManager.h
 * @brief  状態を管理するクラス
 *
 * @author y.akira
 * @date   2016.12.17
 */

#include "precompiled.h"


StateManager::StateManager()
  : index_(0)
{
  // 配列をMAX_STATELIST分確保する
  states_.resize(MAX_STACK);
}

void StateManager::update(float deltaTime, Player* player, StateManager* stateMgr, ofxJoystick& input) {

  // 現在のスタックを処理する
  // 先頭の状態だけhandleInputを呼ぶ
  // if err 状態の無いスタックにアクセスしている, may be pushしたあとにaddしてない
  states_[index_].front()->handleInput(player, stateMgr, input);
  
  // 全ての状態のupdateを呼ぶ
  for (auto& state : states_[index_]) {
    state->update(deltaTime, player, input);
  }
}

void StateManager::draw(Player* player) {

  // 現在のスタックの処理をする
  // 先頭の状態だけdrawを呼ぶ
  states_[index_].front()->draw(player);
}

void StateManager::onCollision(Player* player, Actor*  c_actor) {
  
  // 現在のスタックの処理をする
  // 全ての状態のonCollisionを呼ぶ
  for (auto& state : states_[index_]) {
    state->onCollision(player, c_actor);
  }
}

void StateManager::push() {

  // 設定したスタック領域からはみ出ていないか
  assert(index_ <= MAX_STACK);
  index_++;
}

void StateManager::pop() {

  // スタックの領域からはみ出ていないか
  assert(index_ >= 0);
  states_[index_].clear();
  index_--;
}

void StateManager::add(const shared_ptr<StateBase>& state, Player* player) {
  
  // スタックに積む前にsetupを呼んでおく
  state->setup(player);
  states_[index_].emplace_back(state);
}

void StateManager::remove(const int tag) {
  
  // 現在のスタック領域から
  // 指定されたタグと一致したら削除する
  states_[index_].remove_if(
    [&] (const shared_ptr<StateBase>& state) {
      return state->getTag() == tag;
    }
  );
  
  // 事後報告: removeした後にStateが何もない状態になったら
  // 実行するStateが存在しないのでエラー
  assert(states_[index_].size() != 0);
}
