
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {
  backGround_.setup();
  
  image_.load("Texture/normal2.png");
  rectColor_ = ofFloatColor(0.16, 0.16, 0.16, 1);
  mojiColor_ = ofFloatColor(0.57, 0.57, 0.57, 1);
  rounder_   = 13;
  
  shared_ptr<Spawner> spw = make_shared<Spawner>();
  spw->setActor(make_shared<Player>());
  spw->setSpawnTime(3);
  
  AddActor(spw);
  AddUI(make_shared<uiMeter>());
}

void YanaiScene::update(float deltaTime) {
  backGround_.update(deltaTime);
  
  UpdateActors(deltaTime);
  
  shared_ptr<Actor> player = FindActor("Player");
  if (!player) { return; }
  
  ofLog() << "aa";
  
  auto pos = player->getPos();
  pos.y += 1;
  player->setPos(pos);
  
  UpdateUIs(deltaTime);
}

void YanaiScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Yanai Scene", 20, 20);
  
  backGround_.draw();
  
  ofVec2f pos  = ofGetWindowSize() * 0.5f;
  ofVec2f size = ofVec2f(image_.getWidth(), image_.getHeight());
  pos -= size * 0.5;

  ofRectangle rect(pos, pos + size);
  
  // -----------------------<< 描画 >>---------------------------
  ofPushMatrix();
    ofScale(0.6f, 0.6f);
    ofSetColor(rectColor_);
    ofDrawRectRounded(rect, rounder_);
  
    ofSetColor(mojiColor_);
    image_.draw(rect);
  ofPopMatrix();
  // -----------------------------------------------------------
  
  DrawUIs();
  
  ImGui::Begin("Player");
    ImGui::ColorEdit4 ("Rect Color", &rectColor_.r);
    ImGui::ColorEdit4 ("Moji Color", &mojiColor_.r);
    ImGui::SliderFloat("Rounder"   , &rounder_, 0, 80);
  ImGui::End();
}
