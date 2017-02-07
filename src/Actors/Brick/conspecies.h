
/**
 * @file   conspecies.h
 * @brief  同種
 *
 * @author y.akira
 * @date   2017.01.21
 */

#pragma once


/**
 * @brief Brickと同じように降ってくる仲間
 * @brief BrickManagerで管理するのでBrickフォルダに入れる(よくない
 */
class Conspecies : public Actor {
private:
  ofImage      tex_;
  ofFloatColor texColor_;

  float        timer_;      ///< 生成されてからの時間を計測
  float        spawnTime_;  ///< 生成から当たり判定を有効にするまでに何秒かけるかを設定
  bool         over_;
  ofVec2f      oneTimePos_; ///< 最終的な座標を一時保存
  ofxAnimatableFloat animX_, animY_;  ///< 徐々に大きくする為のアニメーション変数

  ofVec2f      splitSize_;  ///< 縮小用変数
  bool         colPlayer_;  ///< プレイヤーとの接触を判定
  vector<shared_ptr<HomingParticle>> particles_;

  ofVec2f      windowRatio_;///< 画面比率を保存しておく

public:
  Conspecies();
  virtual ~Conspecies() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
  void onCollision(Actor* c_actor) override;
};
