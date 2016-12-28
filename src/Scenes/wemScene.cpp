
/**
 * @file   wemScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void WemScene::setup() {
  cam_.setPosition(0, 0, 300);
  /*
  shared_ptr<Player> player = make_shared<Player>();
  player->setPos(ofVec2f(0, 0));
  shared_ptr<Spawner> spw = make_shared<Spawner>();
  spw->setActor(player);
  spw->setSpawnTime(5);

  AddActor(spw);
  AddActor(make_shared<BrickManager>());
  */
}

void WemScene::update(float deltaTime) {
  UpdateActors(deltaTime);
}

void WemScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Wem Scene", 20, 20);

  cam_.begin();
  DrawActors();
  cam_.end();
}
