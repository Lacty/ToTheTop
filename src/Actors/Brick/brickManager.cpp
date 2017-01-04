
/**
* @file   brickManager.h
* @brief  レンガマネージャー
*
* @author ninja
* @date   2016.12.27
*/

#include "precompiled.h"


BrickManager::BrickManager()
  : deltaTime_( 0 )
{
  name_ = "BrickManager";
  tag_  =  BRICK_MANAGER;

  ofxJSON json;
  json.open("Actor/brickManager.json");
  
  // 画面分割数を取得
  column_ = json["Column"].asInt();
  limit_  = json["Limit"].asInt();
  
  // 配列を再確保
  bricks_.resize(column_);
  
  // Brickのサイズを求める
  {
    auto size  = ofGetWindowWidth() / column_;
    brickSize_ = ofVec2f(size, size);
  }
  
  // Brickのアニメーションや落下時間などを取得
  curve_     = AnimCurve(json["AnimCurve"].asInt());
  fallTime_  = json["FallTime"].asFloat();
  interval_  = json["Interval"].asFloat();
  spawnTime_ = json["SpawnTime"].asFloat();
  
  // 設定された初期地点にBrickを降らせる
  auto size  = json["Start"].size();
  assert(size % column_ == 0);
  
  vector<int> array(size);
  for (int i = 0; i < size; i++) {
    array[i] = json["Start"][i].asInt();
  }
  
  int ii = 0;
  for (int i = 0; i < size; i++) {
    ii = (ii >= column_) ? 0 : ii;
    
    if (array[i]) {
    
      shared_ptr<Brick> brick = make_shared<Brick>();
    
      ofVec2f pos(ii * brickSize_.x, bricks_[ii].size() * brickSize_.x);
      
      brick->setPos(pos + ofVec2f(0, g_local->Height()));
      brick->setSize(brickSize_);
      brick->moveTo(pos, curve_, fallTime_);
    
      AddActor(brick);
      bricks_[ii].emplace_back(brick);
    }
    ii++;
  }
}

void BrickManager::setup() {
  enableUpdate();
}

void BrickManager::update(float deltaTime) {
  deltaTime_ += deltaTime;
  if (deltaTime_ < interval_) { return; }
  deltaTime_ = 0;
  
  shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
  
  int high = 0;
  int low  = bricks_[0].size();
  for (int i = 0; i < column_; i++) {
    high = max(int(bricks_[i].size()), high);
    low  = min(int(bricks_[i].size()), low);
  }
  
  int row;
  
  // 高低差がLimit_以上ある場合は
  if (high >= low + limit_) {
    // 一番低い場所にBrickを落下させる
    for (int i = 0; i < column_; i++) {
      if (low == bricks_[i].size())
        row = i;
    }
  } else {
    // ランダムな位置に落下させる
    row = ofRandom(0, column_);
  }
  
  ofVec2f pos(row * brickSize_.x, bricks_[row].size() * brickSize_.x);
  
  spw->setSpawnTime( spawnTime_        ); // スポーンするまでの時間
  spw->setPos      ( pos               ); // 落下地点
  spw->setSize     ( brickSize_        ); // Brickのサイズ
  spw->set         ( curve_, fallTime_ ); // アニメーションの種類、落下時間
  
  AddActor(spw);
  bricks_[row].emplace_back(spw->getActor());
}

void BrickManager::draw() {}

void BrickManager::gui() {
  if (ImGui::BeginMenu("BrickManager")) {
    ImGui::SliderFloat("Interval",   &interval_, 0, 3);
    ImGui::SliderFloat("Fall Time",  &fallTime_, 0, 3);
    ImGui::SliderFloat("SpawnTime", &spawnTime_, 0, 3);
    ImGui::EndMenu();
  }
}


float BrickManager::getInterval()  const { return interval_;  }
float BrickManager::getSpawnTime() const { return spawnTime_; }
float BrickManager::getFallTime()  const { return fallTime_;  }

// マイナス値はあり得ないのでmaxでセーフティーをかける
void BrickManager::setInterval(float interval) { interval_  = max(0.0f, interval); }
void BrickManager::setSpawnTime(float time)    { spawnTime_ = max(0.0f,     time); }
void BrickManager::setFallTime(float time)     { fallTime_  = max(0.0f,     time); }
