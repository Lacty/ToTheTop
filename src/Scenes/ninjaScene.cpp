
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"



void NinjaScene::setup() {
	cam_.setup();
	bg_.setup();

	AddUI(make_shared<uiTitle>());

	auto brickMgr = make_shared<BrickManager>();
	wp_brickMgr_ = brickMgr;
	AddActor(brickMgr);

	auto player = make_shared<Player>();
	player->setPos(g_local->WindowHalfSize());
	shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
	spwPlayer->setActor(player);
	spwPlayer->setSpawnTime(1);
	AddActor(spwPlayer);
	wp_player_ = player;

	shared_ptr<WarpZone> warpZone = make_shared<WarpZone>();
	warpZone->setSize(ofVec2f(70, 70));
	warpZone->setPos(ofVec2f(g_local->Width() - 100, g_local->HalfHeight() + 100));
	warpZone->setDistination(ofVec2f(g_local->HalfWidth(), g_local->Height() * 2));
	AddActor(warpZone);

	spawn_ = false;
}

void NinjaScene::update(float deltaTime) {
	bg_.update(deltaTime);
	UpdateActors(deltaTime);
	UpdateUIs(deltaTime);

	stageSpawn();

	if (nextSceneTrriger()) { exit(); }
}

void NinjaScene::draw() {
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Ninjya Scene", 20, 20);

	bg_.draw();

	cam_.begin();
	DrawActors();
	cam_.end();

	DrawUIs();
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

void NinjaScene::exit() {
	ClearActors();
	ClearUIs();

	//シーンの移動
}

void NinjaScene::keyPressed(int key) {}

void NinjaScene::stageSpawn() {
	//コンストラクターで生成されたブロックを一旦消去
	if (!wp_brickMgr_.lock()) {
		wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
		return;
	}
	if (auto brickMgr = wp_brickMgr_.lock()) {
		if (brickMgr->shouldUpdate()) {
			brickMgr->disableUpdate();
		}
	}
	//ブロックを平坦に配置する
	if (!spawn_) {
		DeleteActors(BRICK);
		if (auto brickMgr = wp_brickMgr_.lock()) {
			for (int i = 0; i < 5; i++) {
				brickMgr->createBrick(i, 0);
			}
		}
		spawn_ = true;
	}
}

bool NinjaScene::nextSceneTrriger() {
	//プレイヤーが画面外に出たらシーンを移動
	if (auto player = wp_player_.lock()) {
		if (player->getPos().y >= g_local->Height()) {
			return true;
		}
		else return false;
	}
}