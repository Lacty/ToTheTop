
#include "precompiled.h"


std::list<shared_ptr<Actor>> g_actorsList;

void AddActor(const shared_ptr<Actor>& actor) {
  g_actorsList.emplace_back(actor);
}

void UpdateActors(float deltaTime) {
  for (auto& actor : g_actorsList) {
    // setupを実行していなければsetupを実行する
    if (!actor->hasSetup()) {
      actor->setup();
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
      actor->onCollisionEnter(*c_actor);
      c_actor->onCollisionEnter(*actor);
    }
  }
  
  // 削除対象のactorは削除する
  g_actorsList.remove_if(
    [] (const shared_ptr<Actor>& act)->bool {
      return act->isDead();
    }
  );
}

void DrawActors() {
  for (auto& actor : g_actorsList) {
    actor->draw();
  }
}
