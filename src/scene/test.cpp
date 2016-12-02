
#include "test.h"


void TestScene::setup() {
  // testScene.jsonから設定を読み込む
  ofxJson::get().load("game.json");
  string j_path = ofxJson::getString("testScenePath");
  ofxJson::get().load(j_path);
  
  cam_.setPosition(0, 0, 300);
  
  ofVec2f size(20, 20);
  for (int i = -6; i < 6; i++) {
    bricks.push_back(Brick(ofVec3f(size.x * i, -140, 0), size, false));
  }
}

void TestScene::update(float deltaTime) {
  for (auto& brick : bricks) {
    brick.update(deltaTime);
  }
}

void TestScene::draw() {
  ofSetColor(ofColor::white);
  ofDrawBitmapString("Test Scene", 20, 20);
  
  cam_.begin();
  for (auto& brick : bricks) {
    brick.draw();
  }
  
  cam_.end();
}

void TestScene::keyPressed(int key) {}
