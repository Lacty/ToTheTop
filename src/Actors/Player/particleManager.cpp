
/**
* @file   particleManager.h
* @brief  パーティクルマネージャー
*
* @author wem
* @date   2017.1.22
*/

#include "precompiled.h"


ParticleManager::ParticleManager() {}

void ParticleManager::setup() {
  // パーティクルに与える値をJsonから読み込む
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
    // パーティクルを生成する
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
    // 一定数パーティクルを生成したらスイッチをオフに
    isGenerat_ = false;
  }

  for (auto& particle : particles_) {
    particle.update(deltaTime);
  }

  // 一定時間経過したら削除
  particles_.remove_if(
    [](Particle particle)->bool {
      return particle.timeup();
    }
  );
}

void ParticleManager::draw() {
  for (auto& particle : particles_) {
    particle.draw();
  }
}

void ParticleManager::gui() {
  if (ImGui::BeginMenu("Particle_State")) {
    ImGui::SliderFloat("Min_Size-X", &sizeMin_.x, 1.0f, 10.0f);
    ImGui::SliderFloat("Min_Size-Y", &sizeMin_.y, 1.0f, 10.0f);
    ImGui::SliderFloat("Max_Size-X", &sizeMax_.x, 10.0f, 30.0f);
    ImGui::SliderFloat("Max_Size-Y", &sizeMax_.y, 10.0f, 30.0f);

    ImGui::SliderFloat("Min_Vel-X", &velMin_.x, -0.1f, -20.0f);
    ImGui::SliderFloat("Min_Vel-Y", &velMin_.y, -0.1f, -20.0f);
    ImGui::SliderFloat("Max_Vel-X", &velMax_.x, 0.1f, 20.0f);
    ImGui::SliderFloat("Max_Vel-Y", &velMax_.y, 0.1f, 20.0f);

    ImGui::SliderFloat("Limit", &limit_, 0.1f, 5.0f);

    ImGui::EndMenu();
  }
}
