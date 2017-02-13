
#pragma once



class uiTitle :public uiBase {
private:
	int w_, h_;
	ofImage tex_;
	ofVec2f texSize_;
	ofVec2f texPos_;
	ofFloatColor texColor_;
public:
	uiTitle();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};