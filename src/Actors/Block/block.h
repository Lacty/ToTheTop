
#pragma once


class Block : public Actor {
private:
	ofVec2f virtualPos_;

public:
	Block();

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;

	void onCollisionEnter(Actor& c_actor) override;
};