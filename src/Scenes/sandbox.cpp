
#include "precompiled.h"


void Sandbox::setup() {
  // Actorの追加
  // AddActor(make_shared<Player>());
}

void Sandbox::update(float deltaTime) {
  // Actorのupdate
  UpdateActors(deltaTime);
}

void Sandbox::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Sandbox", 20, 20);
  
  // Actorの描画
  DrawActors();
}
