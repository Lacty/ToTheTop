
#pragma once


class Floor : public Actor {
private:
	ofVec2f virtualPos_;

public:
	Floor();

	void setup() override;
	void draw() override;

	void onCollision(Actor* c_actor) override;
};
