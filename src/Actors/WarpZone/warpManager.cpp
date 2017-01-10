
/**
* @file   warpManager.h
* @brief  ワープゾーンマネージャ－
*
* @author f.naoto
* @date   2017.1.8
*/
#include "precompiled.h"


WarpManager::WarpManager() {
	name_ = "WarpManager";
	tag_ = WARP_MANAGER;

	player_ = nullptr;
	warpSize_ = ofVec2f(50, 50);
	spawnPos_ = ofVec2f(ofRandom(0, g_local->Width() - warpSize_.x), g_local->Height());
	destPos_ = ofVec2f(g_local->HalfWidth(), g_local->Height());
}

void WarpManager::setup() {
	warpZone_ = make_shared<WarpZone>();
	warpZone_->setPos(spawnPos_);
	warpZone_->setDistination(ofVec2f(destPos_.x, destPos_.y + warpZone_->getPos().y));
	AddActor(warpZone_);

	enableUpdate();
}

void WarpManager::update(float deltaTime) {
	//生成位置参照用のplayerを取得する
	if (!player_) {
		player_ = FindActor(PLAYER);
		return;
	}

	if (warpZone_->shouldDestroy()) {
		spawnWarp();
	}

	//プレイヤーと一定距離離れた場合、warpZoneを消す
	if ((player_->getPos().y - destPos_.y) > warpZone_->getPos().y) {
		warpZone_->destroy();
	}
}

void WarpManager::gui() {
	if (ImGui::BeginMenu("WarpManager")) {
		ImGui::SliderFloat("WarpZoneSizeX", &warpSize_.x, 1, 100);
		ImGui::SliderFloat("WarpZoneSizeY", &warpSize_.y, 1, 100);
		ImGui::SliderFloat("SpawnPosY", &spawnPos_.y, 1, g_local->Height() * 2);
		ImGui::SliderFloat("DestPosY", &destPos_.y, 1, g_local->Height() * 2);
		ImGui::EndMenu();
	}
}

//ワープゾーンを生成する場所
void WarpManager::spawnWarp() {
	spawnPos_.x = ofRandom(0, g_local->Width() - warpSize_.x);

	warpZone_ = make_shared<WarpZone>();
	warpZone_->setSize(ofVec2f(warpSize_));
	warpZone_->setPos(ofVec2f(spawnPos_.x, spawnPos_.y + player_->getPos().y));
	warpZone_->setDistination(ofVec2f(destPos_.x, destPos_.y + warpZone_->getPos().y));
	AddActor(warpZone_);
}