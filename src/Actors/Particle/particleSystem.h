
/**
 * @file   particleSystem.h
 *
 * @author y.akira
 * @date   2017.01.24
 */

#pragma once
#include <deque>

class Particle;

/// ====================================================
///< @brief パーティクルシステム
/// ====================================================
class ParticleSystem : public Actor {
public:
  using pParticle_t = unique_ptr<Particle>;
  
private:
  bool              play_;                  ///< 実行中か
  float             deltaTime_;             ///< 経過時間
  float             destroyTime_;           ///< 自滅時間
  
  std::deque<pParticle_t> particles_;             ///< ぱーてくるstd::listで管理

  ofVec2f           sizeMin_;
  ofVec2f           sizeMax_;

  ofVec2f           velocityMin_;
  ofVec2f           velocityMax_;
  
  float             createDelta_;
  float             createInterval_;
  float             partDestroyTime_;

  ofFloatColor      startCol_;
  ofFloatColor      endCol_;

  float             sizeRatio_;

  float             gravity_;
  bool              useGravity_;

  void              updateParts(float delta);  ///< ぱーてくる更新
  void              create();                  ///< パーティクル追加

  bool              hasDestroyTime() const;    ///< 自滅時間が設定されているか

public:
  ParticleSystem();
  ParticleSystem(bool activate, float sizeRatio = 1, float destroyTime = 0, bool useGravity = false);
  ParticleSystem(bool activate, ofColor startColor, ofColor endColor,
                 float sizeRatio = 1, float destroyTime = 0, bool useGravity = false);
  ParticleSystem(const ParticleSystem&) = delete;
  virtual ~ParticleSystem() {}

  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
  
  // @param [in] destroyTime 指定した時間になるとパーティクルの生成を止め
  //                         パーティクルが0になったらシステムが自滅する
  void play();
  void stop();
  void killAll();
  
  // ===================================================
  // Getter
  float getInterval() const;
  ofVec2f getSizeMin() const;
  ofVec2f getSizeMax() const;
  ofVec2f getVelocityMin() const;
  ofVec2f getVelocityMax() const;
  
  // ===================================================
  // Setter
  void setInterval(float interval);        ///< 生成区間を設定
  void setSysDestroyTime(float time);
  void setPartDestroyTime(float time);
  void setCreateSize(ofVec2f min, ofVec2f max);
  void setCreateVelocity(ofVec2f min, ofVec2f max);
  void setAnimColor(ofFloatColor start, ofFloatColor end);
};

/// ====================================================
///< @brief パーティクル
/// ====================================================
class Particle : public Actor {
private:
  float deltaTime_;
  float destroyTime_;

  ofFloatColor       startCol_;
  ofFloatColor       endCol_;
  ofxAnimatableFloat r_, g_, b_;

  float              sizeRatio_; ///< 最終的な大きさを元の大きさからどれくらいの倍率にするか
  ofxAnimatableFloat animSizeX_, animSizeY_;

  float gravity_;
  bool  useGravity_;

public:
  Particle();
  virtual ~Particle() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void setDestroyTime(float time);

  void setAnimColor(ofFloatColor start, ofFloatColor end);
  void setSizeRatio(float ratio);
  void setGravity(float gravity);
  void useGravity(bool g);
};
