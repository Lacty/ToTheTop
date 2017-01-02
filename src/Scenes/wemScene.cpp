
/**
 * @file   wemScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void WemScene::setup() {
  cam_.setup();
  bg_.setup();

  originPos_.set(-70, 100);
  destPos_.set(-70, -100);
  brickSize_.set(24, 24);
  round_ = 4;
  time_ = 0.3;

  AddActor(make_shared<BrickManager>());

  shared_ptr<Player> player = make_shared<Player>();
  player->setPos(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
  shared_ptr<Spawner> spw = make_shared<Spawner>();
  spw->setActor(player);
  spw->setSpawnTime(3);
  AddActor(spw);
}

void WemScene::update(float deltaTime) {
  bg_.update(deltaTime);
  UpdateActors(deltaTime);
}

void WemScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Wem Scene", 20, 20);

  bg_.draw();

  cam_.begin();
  DrawActors();
  cam_.end();
}

// Gui用に独立した関数
void WemScene::gui() {
  if (ImGui::BeginMenu("WemScene")) {
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

void WemScene::keyPressed(int key) {
  shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();

  spw->setSpawnTime(1);
  spw->setPos(destPos_);
  spw->setSize(brickSize_);

  spw->set(AnimCurve(curve_), time_);

  AddActor(spw);
}
