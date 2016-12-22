
#pragma once


class Brick : public Actor {
private:
	//イージングに用いる変数
	ofxAnimatableFloat animPosX_;//左右移動も必要であれば配列に変える予定
	ofxAnimatableFloat animPosY_;
	//落下地点
	ofVec2f fallPoint_;

	//落下(イージング)のsetup
	void fallSetup();

	//テスト用変数
	float count_;
public:
	Brick();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* c_actor) override;

	//落下地点を指定する
	void setMoveTo(ofVec2f& pos);
};
