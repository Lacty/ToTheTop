
#include "precompiled.h"


uiTitle::uiTitle() {
	ofxJSON json;
	json.open("user.json");
	w_ = json["Window"]["width"].asInt();
	h_ = json["Window"]["height"].asInt();

	name_ = "uiTitle";
	tag_ = UI_TITLE;

	tex_.load("Texture/titleLogo.png");
	texSize_ = ofVec2f((g_local->Width() / (float)w_) * 300, (g_local->Height() / (float)h_) * 200);
	texPos_ = ofVec2f(g_local->HalfWidth() / 4, g_local->HalfHeight() / 5);
	texColor_ = ofFloatColor(1, 1, 1);
}

void uiTitle::setup() {
	shared_ptr<uiScoreRank> uiScore = make_shared<uiScoreRank>();
	uiScore->disableDrawCurrentScore();
	uiScore->setPos(ofVec2f(g_local->HalfWidth() / 2, g_local->HalfHeight()));
	AddUI(uiScore);

	enableUpdate();
}

void uiTitle::update(float deltaTime) {}

void uiTitle::draw() {
	//アルファ値を操作し、タイトルロゴか操作説明片方を表示
	ofPushStyle();
	ofSetColor(texColor_);
	tex_.draw(texPos_, texSize_.x, texSize_.y);
	ofPopStyle();
}