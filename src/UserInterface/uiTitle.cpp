
#include "precompiled.h"


uiTitle::uiTitle() {
	ofxJSON json;
	json.open("user.json");
	w_ = json["Window"]["width"].asInt();
	h_ = json["Window"]["height"].asInt();

	name_ = "uiTitle";
	tag_ = UI_TITLE;

	log_.load("Texture/titleLogo.png");
	logSize_ = ofVec2f((g_local->Width() / (float)w_) * 250, (g_local->Height() / (float)h_) * 200);
	logPos_ = ofVec2f(g_local->HalfWidth() / 4, g_local->HalfHeight() / 5);
	logColor_ = ofFloatColor(1, 1, 1);

	startLog_.load("Texture/startLogo.png");
	startSize_ = ofVec2f((g_local->Width() / (float)w_) * 250, (g_local->Height() / (float)h_) * 200);
	startPos_ = ofVec2f(g_local->HalfWidth() / 4, g_local->HalfHeight() / 5);
	startColor_ = ofFloatColor(1, 1, 1);

	logoFrag_ = 1;
	changeTime = 5;
	count_ = 0;
	alpha_ = 0;
}

void uiTitle::setup() {
	shared_ptr<uiScoreRank> uiScore = make_shared<uiScoreRank>();
	uiScore->disableDrawCurrentScore();
	uiScore->setPos(ofVec2f(g_local->HalfWidth() / 2, g_local->HalfHeight()));
	AddUI(uiScore);

	enableUpdate();
}

void uiTitle::update(float deltaTime) {
	if (!wp_player_.lock()) {
		wp_player_ = dynamic_pointer_cast<Player>(FindActor(PLAYER));
		return;
	}

	//放置中はタイトルが表示される 
	//何らかの操作をした場合、操作説明が表示される 
	if (auto player = wp_player_.lock()) {
		if (player->getVel().x != 0 || player->getVel().y >= 0.1f) {
			logoFrag_ = 0;
			count_ = 0;
		}
		else {
			count_ += deltaTime;
			if (count_ >= changeTime) {
				logoFrag_ = 1;
			}
		}
	}

	switch (logoFrag_)
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
}

void uiTitle::draw() {
	//アルファ値を操作し、タイトルロゴかスタートロゴを表示 
	ofPushStyle();
	ofSetColor(ofFloatColor(logColor_, 1 - alpha_));
	log_.draw(logPos_, logSize_.x, logSize_.y);
	ofPopStyle();

	ofPushStyle();
	ofSetColor(ofFloatColor(startColor_, alpha_));
	startLog_.draw(startPos_, startSize_.x, startSize_.y);
	ofPopStyle();
}