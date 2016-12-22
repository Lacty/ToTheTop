
#pragma once


class BrickManager :public Actor {
private:
	list<Brick> bricks_;
	float count_;
	int num_;

	void setBrick();
public:
	void sponeBrick();
};