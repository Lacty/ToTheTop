
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
	name_ = "WarpZone";
	tag_ = WARPZONE;
	color_ = ofColor(100, 100, 100, 255);
	size_ = ofVec2f(100, 50);

	tex_.load("Texture/warphole.png");
	tex_.mirror(true, false);
	player_ = nullptr;
}

void WarpZone::setup() {
	enableCollision();
}

void WarpZone::update(float deltaTime) {
	if (!wp_brickMgr_.lock()) {
		wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
		return;
	}

	if (!player_) { return; }
	x_.update(deltaTime);
	y_.update(deltaTime);

	player_->setPos(ofVec2f(x_, y_));
	if (destPos_ == ofVec2f(x_, y_)) {
		if (auto brickMgr = wp_brickMgr_.lock()) {
			brickMgr->enableUpdate();
		}
		player_->canControl(true);
		player_->addVelocity(true);
		destroy();
	}
}

void WarpZone::draw() {
	ofSetColor(color_);
	tex_.draw(ofPoint(pos_.x, pos_.y), size_.x, size_.y);
}

void WarpZone::onCollision(Actor* c_actor) {
	if (player_) { return; }
	if (c_actor->getTag() == PLAYER) {
		color_ = ofFloatColor(0, 0, 0, 0);
		player_ = dynamic_cast<Player*>(c_actor);
		player_->canControl(false);
		player_->addVelocity(false);
		enableUpdate();
	}
	if (auto brickMgr = wp_brickMgr_.lock()) {
		brickMgr->disableUpdate();
	}
}