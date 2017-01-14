
/**
* @file   warpManager.h
* @brief  ワープゾーンマネージャ−
*
* @author f.naoto
* @date   2017.1.8
*/
#include "precompiled.h"


WarpManager::WarpManager() {
	name_ = "WarpManager";
	tag_ = WARP_MANAGER;

	warpSize_ = ofVec2f(100, 100);
	spawnPos_ = ofVec2f(ofRandom(0, g_local->Width() - warpSize_.x), g_local->Height());
	destPos_ = ofVec2f(g_local->HalfWidth(), g_local->Height());
}

void WarpManager::setup() {
	shared_ptr<WarpZone> warpZone;
	warpZone = make_shared<WarpZone>();
	warpZone->setPos(spawnPos_);
	warpZone->setDistination(ofVec2f(destPos_.x, destPos_.y + warpZone->getPos().y));
	AddActor(warpZone);
	wp_warpZone_ = warpZone;

	enableUpdate();
}

void WarpManager::update(float deltaTime) {
	//生成位置参照用のplayerを取得する
	if (!wp_player_.lock()) {
		wp_player_ = FindActor(PLAYER);
		return;
	}
	if (!wp_brickMgr_.lock()) {
		wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
		return;
	}

	if (wp_warpZone_.expired()) {
		for (int i = 0; i < 5; i++) {
			if (auto player = wp_player_.lock()) {
				if (auto brickMgr = wp_brickMgr_.lock()) {
					brickMgr->createBrick(i, player->getPos().y - 200);
				}
			}
		}
		spawnWarp();
	}

	//プレイヤーと一定距離離れた場合、warpZoneを消す
	if (auto warpZone = wp_warpZone_.lock()) {
		if (auto player = wp_player_.lock()) {
			if ((player->getPos().y - destPos_.y) > warpZone->getPos().y) {
				warpZone->destroy();
			}
		}
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

	if (auto player = wp_player_.lock()) {
		shared_ptr<WarpZone> warpZone;
		warpZone = make_shared<WarpZone>();
		warpZone->setSize(ofVec2f(warpSize_));
		warpZone->setPos(ofVec2f(spawnPos_.x, spawnPos_.y + player->getPos().y));
		warpZone->setDistination(ofVec2f(destPos_.x, destPos_.y + warpZone->getPos().y));
		AddActor(warpZone);
		wp_warpZone_ = warpZone;
	}
}