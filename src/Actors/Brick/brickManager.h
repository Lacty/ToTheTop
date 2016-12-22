
#pragma once


class BrickManager :public Actor {
private:
	list<Brick> bricks_;
	list<Brick>::iterator itr_ = bricks_.begin();
	float count_;
	int num_;

	void setBrick();
public:
	void sponeBrick();
};