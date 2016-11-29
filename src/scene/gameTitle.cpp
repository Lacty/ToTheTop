
#include "ofxSceneManager.h"
#include "gameTitle.h"


void GameTitle::setup() {
  font_.load("font/MarkerFelt.ttf", 30);
}

void GameTitle::update(float deltaTime) {}

void GameTitle::draw() {
  string string = "Push Any Key";
  float w = font_.stringWidth(string);  ofPushMatrix();
   ofTranslate(ofGetWidth() * 0.5 - w * 0.5, ofGetHeight() * 0.7);
   font_.drawString(string, 0, 0);
  ofPopMatrix();
}

void GameTitle::keyPressed(int key) {
  // 何かキーが押されたら次のシーンへ遷移する
  getManager()->goToScene(GAME);
}
