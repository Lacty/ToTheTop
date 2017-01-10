
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
  auto brickMgr = make_shared<BrickManager>();
  auto meter    = make_shared<uiMeter>();
  
  ofxJSON json;
  json.open("Actor/leveler.json");
  defaultLevel_  = json["DefaultLevel"].asInt();
  levelInterval_ = json["LevelInterval"].asInt();
  lu_Interval_   = json["LUInterval"].asFloat();
  lu_FallTime_   = json["LUFallTime"].asFloat();
  lu_SpawnTime_  = json["LUSpawnTime"].asFloat();
  level_         = defaultLevel_;
  
  brickMgr_ = brickMgr;
  meter_    = meter;
  
  // 現在のレベルで難易度を初期化
  levelUp(level_);

  // 各機能Managerに追加
  AddActor(brickMgr);
  AddUI(meter);
  enableUpdate();
}

void Leveler::update(float deltaTime) {
  float dist = level_ * levelInterval_;
  float diff = 0;
  
  if (auto meter = meter_.lock()) {
    diff = meter->score() - dist;
  }
  
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
  if (auto brickMgr = brickMgr_.lock()) {
  
    ofLog() << "Level up to : " << level_;
  
    brickMgr->setInterval (brickMgr->getInterval()  - lu_Interval_  * up);
    brickMgr->setFallTime (brickMgr->getFallTime()  - lu_FallTime_  * up);
    brickMgr->setSpawnTime(brickMgr->getSpawnTime() - lu_SpawnTime_ * up);
  }
}
