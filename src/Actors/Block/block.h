
#pragma once


class Block : public Actor {
private:

public:
	Block();

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;

	void onCollisionEnter(Actor& c_actor) override;
};