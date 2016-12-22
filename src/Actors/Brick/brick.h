
#pragma once


class Brick : public Actor {
private:
	//落下地点
	ofVec2f fallPoint_;

	//テスト用
	//ofVec2f startPos_;
	//float time_ = 0;
	//float expo_in(float time, float& startValue, float& currentValue);
	//float count_ = 0;
public:
	Brick();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* c_actor) override;

	//落下地点を指定する
	void moveTo(ofVec2f& pos);
};
