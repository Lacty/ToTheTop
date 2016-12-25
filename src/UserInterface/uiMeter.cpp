
/**
 * @file     uiMeter.h
 * @brief    UI メーター
 *
 * @author   y.akira
 * @date     2016.12.25
 */

#include "precompiled.h"


uiMeter::uiMeter() {
  name_ = "uiMeter";
  ofLog() << "uiMeter()";
}

void uiMeter::setup() {
  ofLog() << "uiMeter::setup()";
  enableUpdate();
}

void uiMeter::update(float deltaTime) {
  ofLog() << "uiMeter::update()";
}

void uiMeter::draw() {
  ofLog() << "uiMeter::draw()";
  ofDrawBitmapString("UI METER", 100, 20);
}
