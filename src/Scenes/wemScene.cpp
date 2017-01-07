
/**
 * @file   wemScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void WemScene::moveCam() {
  ofVec2f pos = cam_.getPos();
  if (pos.y + offsetY_ <= player_->getPos().y) {
    int offset = player_->getPos().y - (pos.y + offsetY_);
    pos.y += offset;
    cam_.setPos(pos);
  }
}

void WemScene::setup() {
  cam_.setup();
  bg_.setup();

  player_ = make_shared<Player>();
  player_->setPos(g_local->WindowHalfSize());
  shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
  spwPlayer->setActor(player_);
  spwPlayer->setSpawnTime(1);
  AddActor(spwPlayer);

  offsetY_ = g_local->Height() * 0.6f;

  AddActor(make_shared<Leveler>());
}

void WemScene::update(float deltaTime) {
  moveCam();

  if (!meter_) {
    meter_ = shared_ptr<uiMeter>(dynamic_cast<uiMeter*>(FindUI(METER).get()));
  }
  else {
    meter_->setCamY(cam_.getPos().y);
  }

  bg_.update(deltaTime);

  UpdateActors(deltaTime);
  UpdateUIs(deltaTime);
}

void WemScene::draw() {
  bg_.draw();

  cam_.begin();
  DrawActors();
  cam_.end();

  DrawUIs();
}

// Gui用に独立した関数
void WemScene::gui() {
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

void WemScene::keyPressed(int key) {}
