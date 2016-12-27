
#pragma once


class BrickManager : public Actor {
private:
	list<shared_ptr<Brick>> bricks_;
	float count_;
	void sponeBrick(ofVec2f& pos);

	ofVec2f fallPoints_[5][10];
	bool existances_[5][10];
	int row_;
	int column_;
	int numX_;
	int numY_;
public:
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};