
/**
 * @file   actorManager.cpp
 * @brief  アクターをマネージメントする関数群が置かれています
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


//! @brief AddActorを使って登録されたアクターはこのリストにまとめられます
std::list<shared_ptr<Actor>> g_actorsList;


/**
 * @brief     アクターを追加します
 * @param     [in] actor 登録するアクターです
 * @note      先にインスタンス化したアクターを登録することも\n
 *            その場でmake_sharedしても登録可能です
 * @attention 無条件でアクターを登録できる
 */
void AddActor(const shared_ptr<Actor>& actor) {
  g_actorsList.emplace_back(actor);
}

/**
 * @brief 登録されたアクターのupdateを呼びます
 * @brief ActorのsetupやonCollisionEnterもここで呼ばれます
 * @param [in] deltaTime 前のフレームから現在のフレームまでにかかった時間を与えます
 * @note  基本的には各シーンで使用するので
 *        そのシーンのupdateにあるdeltaTimeをそのまま渡してください
 */
void UpdateActors(float deltaTime) {
  for (auto& actor : g_actorsList) {
    // setupを実行していなければsetupを実行する
    if (!actor->hasSetup()) {
      actor->setup();
      if (actor->shouldUpdate()) {
        actor->update(deltaTime);
      }
    }
    else
    // updateが有効になっていればupdateを実行
    if (actor->shouldUpdate()) {
      actor->update(deltaTime);
    }
    
    // 当たり判定を実行する場合は処理を続ける
    if (!actor->shouldCollision()) { continue; }
    
    for (auto& c_actor : g_actorsList) {
      // 自分自信との判定は取らない
      if (*actor == *c_actor) { continue; }
      
      // 相手が判定を取る場合のみ処理を続ける
      if (!c_actor->shouldCollision()) { continue; }
      
      // 衝突していれば処理を続ける
      if (!actor->getRectangle().intersects(c_actor->getRectangle())) { continue; }
      
      // どちらも生きていれば処理を続ける
      if (actor->isDead() || c_actor->isDead()) { continue; }
      
      // 各actorに衝突したと伝える
      actor->onCollision(c_actor.get());
      c_actor->onCollision(actor.get());
    }
  }
  
  // 削除対象のactorは削除する
  g_actorsList.remove_if(
    [] (const shared_ptr<Actor>& act)->bool {
      return act->isDead();
    }
  );
}

/**
 * @brief 登録されたアクターのdrawを呼びます
 */
void DrawActors() {
  for (auto& actor : g_actorsList) {
    actor->draw();
  }
}

/**
 * @brief 登録されたアクターのGuiを描画します
 */
void DrawActorsGui() {
  for (auto& actor : g_actorsList) {
    actor->gui();
  }
}

/**
 * @brief 特定のアクターを管理下から削除します
 * @param [in] name 削除したいアクターの名前
 */
void DeleteActors(const string& name) {
  g_actorsList.remove_if(
    [&] (const shared_ptr<Actor>& act)->bool {
      return act->getName() == name;
    }
  );
}

/**
 * @brief 特定のアクターを管理下から削除します
 * @param [in] tag 削除したいアクターのタグ
 */
void DeleteActors(const int tag) {
  g_actorsList.remove_if(
    [&] (const shared_ptr<Actor>& act)->bool {
      return act->getTag() == tag;
    }
  );
}

/**
 * @brief  特定のアクターを取得する
 * @param  [in] name 取得したいアクターの名前
 * @retval アクターを指すスマポを返す
 * @note   見つからなければnullptrを返す
 */
shared_ptr<Actor> FindActor(const string& name) {
  for (auto& act : g_actorsList) {
    if (act->getName() == name) {
      return act;
    }
  }
  
  // 見つからなければnullを返す
  return nullptr;
}

/**
 * @brief  特定のアクターを取得する
 * @param  [in] tag 取得したいアクターのダグ
 * @retval アクターを指すスマポを返す
 * @note   見つからなければnullptrを返す
 */
shared_ptr<Actor> FindActor(const int tag) {
  for (auto& act : g_actorsList) {
    if (act->getTag() == tag) {
      return act;
    }
  }
  
  // 見つからなければnullを返す
  return nullptr;
}

/**
 * @brief  特定のアクターを配列で取得する
 * @param  [in] name 取得したいアクターの名前
 */
list<shared_ptr<Actor>> FindActorsList(const string& name) {
  list<shared_ptr<Actor>> list;
  for (auto& act : g_actorsList) {
    if (act->getName() == name) {
      list.emplace_back(act);
    }
  }
  
  return list;
}

/**
 * @brief 特定のアクターを配列で取得する
 * @param [in] tag 取得したいアクターのタグ
 */
list<shared_ptr<Actor>> FindActorsList(const int tag) {
  list<shared_ptr<Actor>> list;
  for (auto& act : g_actorsList) {
    if (act->getTag() == tag) {
      list.emplace_back(act);
    }
  }
  
  return list;
}
