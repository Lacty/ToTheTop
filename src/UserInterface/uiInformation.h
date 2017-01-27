
#pragma once


class uiInformation :public uiBase {
private:
	vector<string> informations_;
	ofTrueTypeFont font_;
public:
	uiInformation();
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};