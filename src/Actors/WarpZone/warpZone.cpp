
#include "precompiled.h"


void WarpZone::setDistination(const ofVec2f& pos) {
	destPos_ = pos;

	x_.animateFromTo(pos_.x, destPos_.x);
	y_.animateFromTo(pos_.y, destPos_.y);

	x_.setDuration(1);
	y_.setDuration(1);

	x_.setCurve(EASE_IN);
	y_.setCurve(EASE_IN);
}

WarpZone::WarpZone() {
	ofxJSON json;
	json.open("user.json");
	w_ = json["Window"]["width"].asInt();
	h_ = json["Window"]["height"].asInt();

	ofxJSON warpJson;
	warpJson.open("Actor/warpZone.json");
	for (int i = 0; i < warpJson["Color"]["R"].size(); i++) {
		holeColors_.push_back(ofColor(warpJson["Color"]["R"][i].asFloat(),
			warpJson["Color"]["G"][i].asFloat(),
			warpJson["Color"]["B"][i].asFloat()));
		holeScales_.push_back(ofVec2f(0, 0));
	}
	
	name_ = "WarpZone";
	tag_ = WARPZONE;
	color_ = ofColor(255, 255, 255, 255);
	size_ = ofVec2f((g_local->Width() / (float)w_) * 100, (g_local->Height() / (float)h_) * 100);

	player_ = nullptr;
	warp_ = false;
	degree_ = 0;

	holeValue_ = 5;
	holeScale_ = ofVec2f(100, 70);
}

void WarpZone::setup() {
	enableCollision();
	enableUpdate();
}

void WarpZone::update(float deltaTime) {
	if (!wp_brickMgr_.lock()) {
		wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
		return;
	}

	degree_ -= deltaTime * 50;

	for (int i = 0; i < holeScales_.size(); i++) {
		holeScales_[i] += i + 1;
		if (holeScales_[i].x >= size_.x) { holeScales_[i] = ofVec2f(0, 0); }
		if (i == holeScales_.size()) { i = 0; }
	}

	if (!player_&&!warp_) { return; }
	x_.update(deltaTime);
	y_.update(deltaTime);

	player_->setPos(ofVec2f(x_, y_));

	for (int i = 0; i < 3; i++) {
		shared_ptr<Particle> part = make_shared<Particle>();
		auto randSize = ofRandom(0.5f, 1.f);
		part->disableCollision();
		part->enableUpdate();
		part->setPos(player_->getPos() + player_->getSize() / 2);
		part->setVel({ static_cast<float>(ofRandom(-8.f, 8.f)), static_cast<float>(ofRandom(-8.f, 8.f)), 0 });
		part->setSize({ static_cast<float>((i + 1) * randSize), static_cast<float>((i + 1) * randSize), 0 });
		part->setDestroyTime(1.0f);
		part->useGravity(true);
		part->setAnimColor(holeColors_[i], ofColor::white);
		part->setSizeRatio(0.5);

		AddActor(part);
	}

	if (destPos_ == ofVec2f(x_, y_)) {
		if (auto brickMgr = wp_brickMgr_.lock()) {
			brickMgr->enableUpdate();
		}
		player_->enableCollision();
		player_->canControl(true);
		player_->addVelocity(true);
		destroy();
	}
}

void WarpZone::draw() {
	ofSetColor(color_);

	//ワープ開始地点の画像
	for (int i = 0; i < holeColors_.size(); i++) {
		drawWarpHole(holeColors_[i],
			ofVec2f(pos_.x, pos_.y),
			ofVec2f(size_.x - holeScales_[i].x, size_.y - holeScales_[i].y));
	}

	if (!warp_) { return; }
	//ワープ終了地点の画像
	for (int i = 0; i < holeColors_.size(); i++) {
		drawWarpHole(holeColors_[i],
			ofVec2f(destPos_.x, destPos_.y),
			ofVec2f(holeScales_[i].x, holeScales_[i].y));
	}

	for (int i = 0; i < holeValue_; i++) {
		int colorR = ofRandom(150, 250);
		int colorG = ofRandom(150, 250);
		int colorB = ofRandom(150, 250);
		drawHole(ofColor(colorR, colorG, colorB), holePos_[i]);
	}
}

void WarpZone::drawWarpHole(const ofColor& color,const ofVec2f& pos,const ofVec2f& size) {
	ofPushStyle();
	ofPushMatrix();
	ofNoFill();
	ofSetColor(color);
	ofTranslate(ofPoint(pos.x + size.x / 2, pos.y + size.y / 2));
	ofDrawEllipse(-size.x / 2, -size.y / 2, size.x, size.y);
	ofPopMatrix();
	ofPopStyle();
}

void WarpZone::drawHole(const ofColor& color,const ofVec2f& pos) {
	ofPushStyle();
	ofPushMatrix();
	ofNoFill();
	ofSetColor(color);
	ofTranslate(pos);
	//プレイヤーが通り過ぎたら大きくする
	if (pos.y <= player_->getPos().y) {
		float destPosY = player_->getPos().y - pos.y;
		ofScale(destPosY / size_.x, 1);
	}
	ofDrawEllipse(ofVec2f(0, 0), holeScale_.x, holeScale_.y);
	ofPopMatrix();
	ofPopStyle();
}

void WarpZone::onCollision(Actor* c_actor) {
	if (player_) { return; }
	if (c_actor->getTag() == PLAYER) {
		if (auto brickMgr = wp_brickMgr_.lock()) {
			brickMgr->disableUpdate();
		}
		player_ = dynamic_cast<Player*>(c_actor);
		player_->canControl(false);
		player_->addVelocity(false);
		player_->disableCollision();
		warp_ = true;

		for (int i = 0; i < holeValue_; i++) {
			holePos_.push_back(ofVec2f(pos_ + ((destPos_ - pos_) / holeValue_) * (i + 1)));
		}
	}
}