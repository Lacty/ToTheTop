
#pragma once


class BrickManager :public Actor {
private:
	list<shared_ptr<Brick>> bricks_;
	list<shared_ptr<Brick>>::iterator itr_ = bricks_.begin();
	float count_;
	int num_;

	void setBrick();
public:
	void sponeBrick();
};