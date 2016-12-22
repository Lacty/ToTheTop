
#pragma once


class Brick : public Actor {
private:
	//落下地点
	ofVec2f fallPoint_;

	float count_ = 0;
public:
	Brick();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* c_actor) override;

	//落下地点を指定する
	void moveTo(ofVec2f& pos);
};
