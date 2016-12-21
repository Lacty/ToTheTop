
/**
 * @file   sandbox.h
 * @brief  サンドボックスシーン
 *         各自で作った機能を試すためのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


void Sandbox::setup() {
  // Actorの追加
  //AddActor(make_shared<Player>());
}

void Sandbox::update(float deltaTime) {

	count_ += ofGetLastFrameTime();
	if (count_ >= 3) {
		AddActor(make_shared<Brick>());
		count_ = 0;
	}

  // Actorのupdate
  UpdateActors(deltaTime);
}

void Sandbox::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Sandbox", 20, 20);
  
  // Actorの描画
  DrawActors();
}
