
/**
 * @file   brickManager.h
 *
 * @author y.akira
 * @date   2016.12.29
 */

#pragma once


class BrickManager : public Actor {
private:
  

public:
  BrickManager();
  ~BrickManager() {}

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};
