
/**
 * @file   stateManager.h
 * @brief  Actorの状態を管理するクラス
 *
 * @author y.akira
 * @date   2016.12.17
 */

#pragma once


// ==========================================================================
//! 状態の基底クラス
class StateBase {
protected:
  int tag_;
  
public:
  StateBase()
    : tag_(-1)
  {}
  
  ~StateBase() {}
  
  //! 起動後に一度呼ばれます
  virtual void setup(Player* player) {}
  
  //! 入力により状態を変更するために毎フレーム呼ばれます
  virtual void handleInput(Player* player, ofxJoystick& input) {}
  
  //! 毎フレーム呼ばれます
  virtual void update(float deltaTime, Player* player, ofxJoystick& input) {}
  
  //! 描画用に毎フレーム呼ばれます
  virtual void draw(Player* player) {}
  
  //! プレイヤーが別のアクターと衝突した際に呼ばれます
  virtual void onCollision(Player* player, Actor* c_actor) {}
  
  //! タグを返します
  int getTag() const { return tag_; }
};


// ==========================================================================
//! 状態マネージャー
class StateManager {
private:
  const int MAX_STACK    = 10; ///< 管理する状態の最大数(スタック)
  const int MAX_PARALLEL = 5;  ///< 管理する状態の最大数(並列)
  
  using p_state = shared_ptr<StateBase>;
  
  vector<list<p_state>> states_; ///< 状態リスト
  int                   index_;  ///< 操作中のスタックの配列数
  
public:
  StateManager();
  ~StateManager() {}
  
  void update(float deltaTime,
              Player* player,
              ofxJoystick& input);            ///< スタックされた現在の状態のupdateを呼ぶ
  
  void draw(Player* player);                  ///< スタックされた現在の状態のdrawを呼ぶ
  
  void onCollision(Player* player,
                   Actor*  c_actor);          ///< スタックされた現在のonCollisionを呼ぶ
  
  void push();                                ///< スタックを次に進める
  void pop();                                 ///< スタックを前に戻す
  
  void add(const p_state& state, Player* player); ///< 状態を追加する
  void remove(const int tag);                     ///< 特定の状態を削除する
};
