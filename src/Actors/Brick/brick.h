
#pragma once


class Brick : public Actor {
private:
	//イージングに用いる変数
	ofxAnimatableFloat animPos_[2];
	//落下地点
	ofVec2f fallPoint_;

	//落下(イージング)のsetup
	void fallSetup();
public:
	Brick();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* c_actor) override;

	//落下地点を指定する
	void moveTo(ofVec2f& pos);
};
