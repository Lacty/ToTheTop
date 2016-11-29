
#include "ofxSceneManager.h"
#include "gameMain.h"


void GameMain::setup() {}

void GameMain::update(float deltaTime) {}

void GameMain::draw() {
  ofDrawBitmapString("Game Main", 20, 20);
}

void GameMain::keyPressed(int key) {
  if (key == '1') {
    getManager()->goToScene(TITLE);
  }
}
