
#pragma once


class Brick : public Actor {
private:
	ofxAnimatableFloat animPosX_;
	ofxAnimatableFloat animPosY_;
	ofVec2f fallPoint_;

	void fallSetup();

	float count_;
public:
	Brick();

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;

	void onCollision(Actor* c_actor) override;
};
