
/**
* @file   brick.h
* @brief  レンガ
*
* @author y.akira
* @date   2016.12.14
*/

#pragma once


//! @brief プレイヤークラス
class Brick : public Actor {
private:

public:
  Brick();

  void setup() override;
  void update(float deltaTime) override;
  void draw() override;

  void onCollisionEnter(Actor& c_actor) override;
};
