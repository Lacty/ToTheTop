
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

void StateManager::update(float deltaTime, Actor* actor) {
  for (auto& state : states_[index_]) {
    state->update(deltaTime, actor);
  }
}
void StateManager::draw(Actor* actor) {
  for (auto& state : states_[index_]) {
    state->draw(actor);
  }
}

void StateManager::push() {
  assert(index_ <= MAX_STACK);
  index_++;
}

void StateManager::pop() {
  assert(index_ >= 0);
  states_[index_].clear();
  index_--;
}

void StateManager::add(const shared_ptr<StateBase>& state, Actor* actor) {
  state->setup(actor);
  states_[index_].emplace_back(state);
}

void StateManager::remove(const int tag) {
  states_[index_].remove_if(
    [&] (const shared_ptr<StateBase>& state) {
      return state->getTag() == tag;
    }
  );
}
