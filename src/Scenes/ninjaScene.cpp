
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void NinjaScene::moveCam() {
	ofVec2f pos = cam_.getPos();
	if (pos.y + offsetY_ <= player_->getPos().y) {
		int offset = player_->getPos().y - (pos.y + offsetY_);
		pos.y += offset;
		cam_.setPos(pos);
	}
}

void NinjaScene::setup() {
	cam_.setup();
	bg_.setup();

	offsetY_ = g_local->Height() * 0.6f;

	AddActor(make_shared<BrickManager>());

	player_ = make_shared<Player>();
	player_->setPos(g_local->WindowHalfSize());
	shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
	spwPlayer->setActor(player_);
	spwPlayer->setSpawnTime(2);
	AddActor(spwPlayer);

	shared_ptr<WarpZone> warpZone = make_shared<WarpZone>();
	warpZone->setPos(ofVec2f(ofGetWindowWidth() / 2 + 100, ofGetWindowHeight() / 2 + 100));
	warpZone->setSize(ofVec2f(40, 40));
	warpZone->setDistination( ofVec2f( g_local->HalfWidth(), g_local->Height()*2 ) );
	AddActor(warpZone);
}

void NinjaScene::update(float deltaTime) {
	bg_.update(deltaTime);
	UpdateActors(deltaTime);

	moveCam();
}

void NinjaScene::draw() {
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Ninjya Scene", 20, 20);

	bg_.draw();

	cam_.begin();
	DrawActors();
	cam_.end();
}

// Gui用に独立した関数
void NinjaScene::gui() {
	if (ImGui::BeginMenu("NinjaScene")) {
		ImGui::Text("this is test scene.");
		ImGui::EndMenu();
	}

	// 背景のGuiを描画
	bg_.gui();

	// アクターのGuiを描画
	DrawActorsGui();

	// UIのGuiを描画
	DrawUIsGui();
}

void NinjaScene::keyPressed(int key) {}