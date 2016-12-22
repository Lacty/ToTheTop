
#pragma once


class BrickManager :public Actor {
private:
	list<Brick> bricks_;
	float count_;

	void setBrick();
public:
	void sponeBrick();
	void updateBricks();
};