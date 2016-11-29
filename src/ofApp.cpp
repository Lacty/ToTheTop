
#include "ofApp.h"
#include "scene/gameTitle.h"
#include "scene/gameMain.h"


void ofApp::setup() {
  sceneManager = ofxSceneManager::instance();
  sceneManager->setDrawDebug(false);
  
  sceneManager->addScene(new GameTitle(), TITLE);
  sceneManager->addScene(new GameMain(),  GAME);
  
  sceneManager->setCurtainDropTime(0.5);
  sceneManager->setCurtainRiseTime(0.5);
}

void ofApp::update() {
  sceneManager->update(ofGetLastFrameTime());
}

void ofApp::draw() {
  sceneManager->draw();
}


void ofApp::keyPressed(int key) {
  sceneManager->keyPressed(key);
}
