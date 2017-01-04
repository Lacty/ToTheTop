
/**
 * @file   leveler.h
 *
 * @author y.akira
 * @date   2017.01.04
 */

#include "precompiled.h"


Leveler::Leveler()
  : level_         ( 0 )
  , defaultLevel_  ( 0 )
  , levelInterval_ ( 0 )
  , lu_Interval_   ( 0 )
  , lu_FallTime_   ( 0 )
  , lu_SpawnTime_  ( 0 )
{}

void Leveler::setup() {
  brickMgr_ = make_shared<BrickManager>();
  meter_    = make_shared<uiMeter>();
  
  ofxJSON json;
  json.open("Actor/leveler.json");
  defaultLevel_  = json["DefaultLevel"].asInt();
  levelInterval_ = json["LevelInterval"].asInt();
  lu_Interval_   = json["LUInterval"].asFloat();
  lu_FallTime_   = json["LUFallTime"].asFloat();
  lu_SpawnTime_  = json["LUSpawnTime"].asFloat();
  level_         = defaultLevel_;
  
  // 現在のレベルで難易度を初期化
  levelUp(level_);

  // 各機能Managerに追加
  AddActor(brickMgr_);
  AddUI(meter_);
  enableUpdate();
}

void Leveler::update(float deltaTime) {
  float dist = level_ * levelInterval_;
  float diff = meter_->score() - dist;
  
  // スコアが増えていたら処理を続ける
  if (diff <= 0) { return; }
  
  int up = int(diff / levelInterval_);
  
  // 難易度を上げるラインに到達しているか？
  if (up <= 0) { return; }
  
  level_ += up;
  levelUp(up);
}

void Leveler::gui() {}


void Leveler::levelUp(int up) {
  if (!brickMgr_) { return; }
  
  ofLog() << "Level up to : " << level_;
  
  brickMgr_->setInterval (brickMgr_->getInterval()  - lu_Interval_  * up);
  brickMgr_->setFallTime (brickMgr_->getFallTime()  - lu_FallTime_  * up);
  brickMgr_->setSpawnTime(brickMgr_->getSpawnTime() - lu_SpawnTime_ * up);
}
