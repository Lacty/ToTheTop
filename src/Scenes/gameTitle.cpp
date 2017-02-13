
/**
 * @file   gameTitle.h
 * @brief  ゲームタイトルのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


void GameTitle::setup() {  
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

void GameTitle::update(float deltaTime) {
	bg_.update(deltaTime);
	UpdateActors(deltaTime);
	UpdateUIs(deltaTime);

	stageSpawn();

	if (nextSceneTrriger()) { exit(); }
}

void GameTitle::draw() {
	bg_.draw();

	cam_.begin();
	DrawActors();
	cam_.end();

	DrawUIs();
}

void GameTitle::gui() {
	// 背景のGuiを描画
	bg_.gui();

	// アクターのGuiを描画
	DrawActorsGui();

	// UIのGuiを描画
	DrawUIsGui();
}

void GameTitle::exit() {
	ClearActors();
	ClearUIs();
}

void GameTitle::stageSpawn() {
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

bool GameTitle::nextSceneTrriger() {
	//プレイヤーが画面外に出たらシーンを移動
	if (auto player = wp_player_.lock()) {
		if (player->getPos().y >= g_local->Height()) {
			return true;
		}
		else return false;
	}
}