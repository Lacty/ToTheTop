
#pragma once


class Brick : public Actor {
private:
	ofxAnimatableFloat animPos_;
	ofVec2f defaultVel_;
	ofVec2f fallPoint_;

	int yMargin_;
	int hightCol_;

	float count_;
public:
	Brick();

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;

	void onCollision(Actor* c_actor) override;
};
