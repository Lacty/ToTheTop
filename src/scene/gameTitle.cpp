
#include "ofxSceneManager.h"
#include "gameTitle.h"


void GameTitle::setup() {}

void GameTitle::update(float deltaTime) {}

void GameTitle::draw() {
  ofDrawBitmapString("Game Title", 20, 20);
}

void GameTitle::keyPressed(int key) {
  if (key == 't') {
    getManager()->goToScene(GAME);
  }
}
