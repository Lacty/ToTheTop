
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
	ofxAnimatableFloat x_, y_;
  float              round_;
  
public:
	Brick();
	virtual ~Brick() {}
  
  virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
  
	virtual void onCollision(Actor* c_actor) override;
  
  
  void moveTo(const ofVec2f& pos, AnimCurve curve, float time);
  void moveTo(float x, float y, AnimCurve curve, float time);
  
  void setRectRound(float r);
};
