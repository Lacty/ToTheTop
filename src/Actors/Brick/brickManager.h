
#pragma once
#include <random>


class BrickManager :public Actor {
private:
	list<Brick> bricks_;
	int row_ = 10;
	int column_ = 5;
	ofVec2f fallPoints_[5][10];
	bool existences_[5][10];
	float count_;
	int numX_;
	int numY_;

	float a = 0;

	void setBrick();
	void spone();
public:
	void setup();
	void update(float& deltaTime);
};