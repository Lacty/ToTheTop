
#include "precompiled.h"


uiTitle::uiTitle() {
	name_ = "uiTitle";
	tag_ = UI_TITLE;

	tex_.load("Texture/titleLogo.png");
	texSize_ = ofVec2f(300, 200);
	texPos_ = ofVec2f(g_local->HalfWidth() / 4, g_local->HalfHeight() / 5);
	texColor_ = ofFloatColor(1, 1, 1);

	information_ = 1;
	changeTime = 5;
	count_ = 0;
	alpha_ = 0;
}

void uiTitle::setup() {
	joy_.setup(GLFW_JOYSTICK_1);

	shared_ptr<uiInformation> uiInfo = make_shared<uiInformation>();
	uiInfo->setPos(ofVec2f(g_local->HalfWidth() / 4, g_local->HalfHeight() / 4));
	AddUI(uiInfo);
	wp_uiInfo_ = uiInfo;

	shared_ptr<uiScoreRank> uiScore = make_shared<uiScoreRank>();
	uiScore->disableDrawCurrentScore();
	uiScore->setPos(ofVec2f(g_local->HalfWidth() / 2, g_local->HalfHeight()));
	AddUI(uiScore);

	enableUpdate();
}

void uiTitle::update(float deltaTime) {
	//放置中はタイトルが表示される
	//何らかの操作をした場合、操作説明が表示される
	if (joy_.anyButton()) {
		information_ = 0;
		count_ = 0;
	}
	else {
		count_ += deltaTime;
		if (count_ >= changeTime) {
			information_ = 1;
		}
	}
	switch (information_)
	{
	case 0:
		alpha_ += deltaTime / 2;
		if (alpha_ >= 1) { alpha_ = 1; }
		break;
	case 1:
		alpha_ -= deltaTime / 2;
		if (alpha_ <= 0) { alpha_ = 0; }
		break;
	}

	//アルファ値を操作し、タイトルロゴか操作説明片方を表示
	if (auto uiInfo = wp_uiInfo_.lock()) {
		uiInfo->setColor(ofFloatColor(uiInfo->getColor(), alpha_));
	}
}

void uiTitle::draw() {
	//アルファ値を操作し、タイトルロゴか操作説明片方を表示
	ofPushStyle();
	ofSetColor(ofFloatColor(texColor_, 1 - alpha_));
	tex_.draw(texPos_, texSize_.x, texSize_.y);
	ofPopStyle();
}