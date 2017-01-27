
#include "precompiled.h"


uiInformation::uiInformation() {
	name_ = "uiInformation";
	tag_ = INFORMATION;
}

void uiInformation::setup() {
	font_.load("Font/gothic.ttf", 30);

	ofxJSON json;
	json.open("UI/information.json");
	for (int i = 0; i < json["sentence"].size(); i++) {
		informations_.push_back(json["sentence"][i].asString());
	}
}

void uiInformation::update(float deltaTime) {}

void uiInformation::draw() {
	ofPushStyle();
	ofSetColor(color_);
	float stringHight = font_.stringHeight("A");
	for (int i = 0; i < informations_.size(); i++) {
		font_.drawString(informations_[i], pos_.x, pos_.y + (stringHight*i));
	}
	ofPopStyle();
}