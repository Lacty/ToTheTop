
/**
* @file   particleManager.h
* @brief  �p�[�e�B�N���}�l�[�W���[
*
* @author wem
* @date   2017.1.22
*/

#include "precompiled.h"


ParticleManager::ParticleManager() {}

void ParticleManager::setup() {
  // �p�[�e�B�N���ɗ^����l��Json����ǂݍ���
  ofxJSON json;
  json.open("Actor/particle.json");
  sizeMin_ = ofVec2f(json["Size"]["Width"]["min"].asFloat(),
                     json["Size"]["Height"]["min"].asFloat());
  sizeMax_ = ofVec2f(json["Size"]["Width"]["max"].asFloat(),
                     json["Size"]["Height"]["max"].asFloat());
  velMin_  = ofVec2f(json["Velocity"]["X"]["min"].asFloat(),
                     json["Velocity"]["Y"]["min"].asFloat());
  velMax_  = ofVec2f(json["Velocity"]["X"]["max"].asFloat(),
                     json["Velocity"]["Y"]["max"].asFloat());
  limit_   = json["Limit"].asFloat();

  isGenerat_ = false;
}

void ParticleManager::update(float deltaTime) {
  if (isGenerat_) {
    // �p�[�e�B�N���𐶐�����
    for (int i = 0; i < 10; i++) {
      ofVec2f rs = ofVec2f(ofRandom(sizeMin_.x, sizeMax_.x),
                           ofRandom(sizeMin_.y, sizeMax_.y));
      ofVec2f rv = ofVec2f(ofRandom(velMin_.x, velMax_.x),
                           ofRandom(velMin_.y, velMax_.y));

      Particle particle;
      particle.setPos(pos_);
      particle.setSize(rs);
      particle.setVel(rv);
      particle.setColor(color_);
      particle.setLimit(limit_);
      particles_.emplace_back(particle);
    }
    // ��萔�p�[�e�B�N���𐶐�������X�C�b�`���I�t��
    isGenerat_ = false;
  }

  for (auto& particle : particles_) {
    particle.update(deltaTime);
  }

  // ��莞�Ԍo�߂�����폜
  particles_.remove_if(
    [](Particle particle)->bool {
      return particle.timeup();
    }
  );
}

void ParticleManager::draw() {
  if (particles_.size() != 0) {
    for (auto& particle : particles_) {
      particle.draw();
    }
  }
}

void ParticleManager::gui() {}
