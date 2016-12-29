
/**
 * @file   spawner.h
 * @brief  Actorを生成するクラス
 *
 * @author y.akira
 * @date   2016.12.28
 */

#pragma once


/**
 * @brief 一定条件下でActorを生成するクラス
 */
class Spawner : public Actor {
protected:
  shared_ptr<Actor> actor_;
  
  float spawnTime_;
  float deltaTime_;
  
  bool shouldSpawn();

public:
  Spawner();
  Spawner(const shared_ptr<Actor>& act, float timer);
  virtual ~Spawner() {}
  
  virtual void setup() override;
  virtual void update(float deltaTime) override;
  virtual void draw() override;
  
  //! 設定されたアクターをactorManagerに登録します
  void         spawn();
  
  //! 経過時間をリセットします
  void         resetTimer();
  
  //! 設定したアクターを生成する時間を設定します
  void         setSpawnTime(float time);
  
  //! 生成するアクターを設定します
  void         setActor(const shared_ptr<Actor>&  act);
  void         setActor(const shared_ptr<Actor>&& act);
  
  //! 設定されたアクターを返します
  shared_ptr<Actor> getActor() const;
};
