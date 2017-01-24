
#pragma once



class uiTitle :public uiBase {
private:
	ofxJoystick joy_;
	ofImage tex_;
	ofVec2f texSize_;
	ofVec2f texPos_;
	ofFloatColor texColor_;
	weak_ptr<uiInformation> wp_uiInfo_;
	float changeTime;
	int information_;
	float count_;
	float alpha_;
public:
	uiTitle();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};