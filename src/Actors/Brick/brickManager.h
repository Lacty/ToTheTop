
#pragma once


class BrickManager :public Actor {
private:
	list<Brick> bricks_;
	list<Brick>::iterator itr_=bricks_.begin();
	int row_ = 10;
	int column_ = 5;
	ofVec2f fallPoints_[5][10];
	bool existences_[5][10];
	float count_;
	int numX_;
	int numY_;

	void setBrick();
	void spone(float& deltaTime);
public:
	void setup();
	void update(float& deltaTime);
};