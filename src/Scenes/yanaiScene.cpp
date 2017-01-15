
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


void YanaiScene::setup() {}

void YanaiScene::exit() {}

void YanaiScene::update(float deltaTime) {}

void YanaiScene::draw() {}

void YanaiScene::gui() {}

void YanaiScene::keyPressed(int key) {
  if (key == 'z') {
    PlaySound(SoundTag::JUMP);
  }
  if (key == 'x') {
    PlaySound(SoundTag::DUCK);
  }
  if (key == 'c') {
    PlaySound(SoundTag::TELEPORT_USE);
  }
  if (key == 'v') {
    PlaySound(SoundTag::TELEPORT_REUSEABLE);
  }
}
