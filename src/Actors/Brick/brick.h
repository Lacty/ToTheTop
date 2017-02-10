﻿
/**
 * @file   brick.h
 * @brief  レンガ
 *
 * @author y.akira
 * @date   2016.12.29
 */

#pragma once


class Brick : public Actor {
private:
	ofxAnimatableFloat x_, y_, r_;
  float              round_;
  
  bool               isFinishAnimating_;
  
  bool               playOnce_;

public:
	Brick();
	virtual ~Brick() {}
  
  virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
  
	virtual void onCollision(Actor* c_actor) override;
  
  const ofVec2f getFallPos();
  
  //! 指定した位置に移動させる
  void moveTo(const ofVec2f& pos, AnimCurve curve, float time);
  void moveTo(float x, float y, AnimCurve curve, float time);
  
  //! 矩形の角を丸める数値を設定する
  void setRectRound(float r);
  
  bool isAnimating() const;
};
