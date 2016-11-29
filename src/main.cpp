
#include "ofMain.h"
#include "ofApp.h"

#include "ofxJsonSettings.h"


int main() {
  ofxJson::get().load("user.json");
  int w = ofxJson::getInt("window/width");
  int h = ofxJson::getInt("window/height");
  int f = ofxJson::getBool("window/fullScreen");
  int fps = ofxJson::getInt("window/frameLimit");

  ofSetupOpenGL(w, h, f ? OF_FULLSCREEN : OF_WINDOW);
  ofSetFrameRate(fps);
  
  ofRunApp(new ofApp());
}
