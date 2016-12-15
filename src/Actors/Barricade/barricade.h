
#pragma once


class Barricade : public Actor {
private:
	ofVec2f virtualPos_;

public:
	Barricade();

	void setup() override;
	void draw() override;

	void onCollisionEnter(Actor& c_actor) override;
};