
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::moveCam() {
  ofVec2f pos = cam_.getPos();
  
  // nullチェックとshared_ptrのコピーを行う
  if (auto player = player_.lock()) {
  
    if (pos.y + camOffsetMax_ <= player->getPos().y) {
      int offset = player->getPos().y - (pos.y + camOffsetMax_);
      pos.y += offset;
      cam_.setPos(pos);
    }
    if (pos.y + camOffsetMin_ >= player->getPos().y) {
      int offset = player->getPos().y - (pos.y + camOffsetMin_);
      pos.y += offset;
      cam_.setPos(pos);
    }
  }
}

void YanaiScene::setup() {
  cam_.setup();
  bg_.setup();
  
  auto player = make_shared<Player>();
  player->setPos(g_local->WindowHalfSize());
  shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
  spwPlayer->setActor(player);
  spwPlayer->setSpawnTime(1);
  AddActor(spwPlayer);
  
  player_ = player;
  
  camOffsetMax_ = g_local->Height() * 0.6f;
  camOffsetMin_ = g_local->Height() * 0.2f;
  
  AddActor(make_shared<Leveler>());
}

void YanaiScene::exit() {
  ofLog() << "YanaiScene exit";
  
  // 登録されたアクターとUIを削除
  ClearActors();
  ClearUIs();
}

void YanaiScene::update(float deltaTime) {
  moveCam();
  
  if (auto meter = meter_.lock()) {
    meter->setCamY(cam_.getPos().y);
  } else {
    meter = dynamic_pointer_cast<uiMeter>(FindUI(METER));
    meter_ = meter;
  }
  
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
