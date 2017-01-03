
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {
  cam_.setup();
  bg_.setup();
  
  AddActor(make_shared<BrickManager>());
  
  shared_ptr<Player> player = make_shared<Player>();
  player->setPos(g_local->WindowHalfSize());
  shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
  spwPlayer->setActor(player);
  spwPlayer->setSpawnTime(3);
  AddActor(spwPlayer);
  
  AddUI(make_shared<uiMeter>());
}

void YanaiScene::update(float deltaTime) {
  bg_.update(deltaTime);
  
  UpdateActors(deltaTime);
  UpdateUIs(deltaTime);
}

void YanaiScene::draw() {
  bg_.draw();
  
  cam_.begin();
   DrawActors();
  cam_.end();
  
  DrawUIs();
}

// Gui用に独立した関数
void YanaiScene::gui() {
  if (ImGui::BeginMenu("YanaiScene")) {
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

void YanaiScene::keyPressed(int key) {}
