
/**
 * @file   spawner.cpp
 * @brief  Actorを生成するクラス
 *
 * @author y.akira
 * @date   2016.12.28
 */

#include "precompiled.h"


Spawner::Spawner()
  : spawnTime_( 0 )
  , deltaTime_( 0 )
{
  name_ = "Spawner";
  tag_  =  SPAWNER ;
}

Spawner::Spawner(const shared_ptr<Actor>& act, float timer)
  : actor_    ( act   )
  , deltaTime_( 0     )
  , spawnTime_( timer )
{
  name_ = "Spawner";
  tag_  =  SPAWNER ;
}

void Spawner::setup() {
  enableUpdate();
}

void Spawner::update(float deltaTime) {
  deltaTime_ += deltaTime;
  if (!shouldSpawn()) { return; }
  
  spawn();
}

void Spawner::draw() {}

void Spawner::spawn() {
  // 設定されたアクターが空ならエラー
  assert(actor_ != nullptr);
  
  AddActor(actor_);
  destroy();
}

bool Spawner::shouldSpawn()                     { return deltaTime_ > spawnTime_; }

void Spawner::resetTimer()                      { deltaTime_ = 0;    }
void Spawner::setSpawnTime(float time)          { spawnTime_ = time; }
  
void Spawner::setActor(const shared_ptr<Actor>&  act) { actor_ = act; }
void Spawner::setActor(const shared_ptr<Actor>&& act) { actor_ = act; }

shared_ptr<Actor> Spawner::getActor() const { return actor_; }
