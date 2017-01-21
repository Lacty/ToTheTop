
/**
 * @file   conspecies.h
 * @brief  同種
 *
 * @author y.akira
 * @date   2017.01.21
 */

#pragma once


/**
 * @brief Brickと同じように降ってくる仲間
 * @brief BrickManagerで管理するのでBrickフォルダに入れる(よくない
 */
class Conspecies : public Actor {
private:

public:
  Conspecies();
  virtual ~Conspecies() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void onCollision(Actor* c_actor) override;
};
