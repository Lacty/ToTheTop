
#include "ofxSceneManager.h"
#include "gameMain.h"


void GameMain::setup() {}

void GameMain::update(float deltaTime) {}

void GameMain::draw() {}

void GameMain::keyPressed(int key) {
  if (key == 't') {
    getManager()->goToScene(TITLE);
  }
}
