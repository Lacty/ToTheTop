
#pragma once



class uiTitle :public uiBase {
private:
	int w_, h_;
	ofImage log_,startLog_;
	ofVec2f logSize_,startSize_;
	ofVec2f logPos_,startPos_;
	ofFloatColor logColor_,startColor_;
	weak_ptr<Player> wp_player_;
	float changeTime;
	int logoFrag_;
	float count_;
	float alpha_;
public:
	uiTitle();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};