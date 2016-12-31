﻿
/**
 * @file   brickManager.h
 *
 * @author y.akira
 * @date   2016.12.29
 */

#pragma once


class BrickSpawner;

class BrickManager : public Actor {
private:
  vector<list<shared_ptr<Actor>>> bricks_;

  int                 column_;
  ofVec2f             brickSize_;
  
  AnimCurve           curve_;
  float               spawnTime_;
  float               fallTime_;
  
  float               deltaTime_;
  float               interval_;

public:
  BrickManager();
  ~BrickManager() {}

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
  void gui() override;
  
  void setInterval(float interval);
};
