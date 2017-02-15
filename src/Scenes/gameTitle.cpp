
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

	shared_ptr<Brick> brick = make_shared<Brick>();
	brick->setPos(ofVec2f(0, 0));
	brick->setSize(ofVec2f(g_local->Width(), 100));
	AddActor(brick);

	auto player = make_shared<Player>();
	player->setPos(g_local->WindowHalfSize());
	AddActor(player);
	wp_player_ = player;

	shared_ptr<WarpZone> warpZone = make_shared<WarpZone>();
	warpZone->setPos(ofVec2f(g_local->Width() - 70, g_local->HalfHeight() + 100));
	warpZone->setDistination(ofVec2f(g_local->HalfWidth(), g_local->Height() + warpZone->getPos().y));
	AddActor(warpZone);

	AddUI(make_shared<uiTitle>());
}

void GameTitle::update(float deltaTime) {
	if (nextSceneTrriger()) { exit(); }

	bg_.update(deltaTime);
	UpdateActors(deltaTime);
	UpdateUIs(deltaTime);
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

bool GameTitle::nextSceneTrriger() {
	//プレイヤーが画面外に出たらシーンを移動
	if (auto player = wp_player_.lock()) {
		if (player->getPos().y >= g_local->Height()) {
			return true;
		}
		else return false;
	}
}