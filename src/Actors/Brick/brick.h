
#pragma once


class Brick : public Actor {
private:
	ofxAnimatableFloat animPos_;
	//落下地点
	ofVec2f fallPoint_;
	float c;
	AnimCurve curve = (AnimCurve)(EASE_OUT);

	//イージングのsetup
	void fallSetup();
public:
	Brick();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* c_actor) override;
	
	//落下地点を指定する
	void moveTo(ofVec2f& pos);
	ofVec2f getFallPoint();
};
