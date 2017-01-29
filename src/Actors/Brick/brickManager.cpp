
/**
* @file   brickManager.h
* @brief  レンガマネージャー
*
* @author ninja
* @date   2016.12.27
*/

#include "precompiled.h"


BrickManager::BrickManager()
  : column_       ( 0    )
  , verticalLimit_( 0    )
  , deltaTime_    ( 0    )
  , spawnInterval_( 0    )
  , brickSize_    ( 0, 0 )
  , spawnTime_    ( 0    )
  , fallTime_     ( 0    )
  , curve_        ( AnimCurve::LINEAR )
  , cspDeltaTime_ ( 0    )
{
  name_ = "BrickManager";
  tag_  =  BRICK_MANAGER;

  ofxJSON json;
  json.open("Actor/brickManager.json");
  
  // 画面分割数を取得
  column_ = json["Column"].asUInt();
  verticalLimit_  = json["Limit"].asUInt();
  
  // 配列を再確保
  bricks_.resize(column_);
  
  // Brickのサイズを求める
  {
    float size  = (float)g_local->Width() / column_;
    brickSize_  = ofVec2f(size, size);
  }
  
  // Brickのアニメーションや落下時間などを取得
  curve_          = AnimCurve(json["AnimCurve"].asInt());
  fallTime_       = json["FallTime"].asFloat();
  spawnInterval_  = json["Interval"].asFloat();
  spawnTime_      = json["SpawnTime"].asFloat();
  
  // 設定された初期地点にBrickを降らせる
  const auto size  = json["Start"].size();
  assert(size % column_ == 0);
  
  for (Json::ArrayIndex i = 0; i < size; i++) {
    const auto ii = (i >= column_) ? 0 : i;
    if (json["Start"][i].asBool()) {
    
      shared_ptr<Brick> brick = make_shared<Brick>();
    
      const ofVec2f pos(ii * brickSize_.x, bricks_[ii].size() * brickSize_.x);
      
      brick->setPos(pos + ofVec2f(0, g_local->Height()));
      brick->setSize(brickSize_);
      brick->moveTo(pos, curve_, fallTime_);
    
      AddActor(brick);
      bricks_[ii].emplace_back(brick);
    }
  }
  
  // 仲間の生成パラメータ読み込み
  cspInterval_ = json["CspInterval"].asFloat();
}

void BrickManager::setup() {
  enableUpdate();
}

void BrickManager::update(float deltaTime) {
  deltaTime_    += deltaTime;
  cspDeltaTime_ += deltaTime;
  
  // ==============================================================
  // Brickの生成
  if (deltaTime_ > spawnInterval_) {
    deltaTime_ = 0;
  
    shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
  
    std::size_t high = 0;
    std::size_t low  = bricks_[0].size();
    for (std::size_t i = 0; i < column_; i++) {
      high = max(bricks_[i].size(), high);
      low  = min(bricks_[i].size(), low);
    }
  
    std::size_t col;
  
    // 高低差がLimit以上ある場合は
    if (high >= low + verticalLimit_) {
      // 一番高い所以外の場所のどこかにBrickを落下させる
      vector<std::size_t> arr;
      arr.reserve(column_ / 2);
      for (std::size_t i = 0; i < column_; i++) {
        if (high != bricks_[i].size())
          arr.emplace_back(i);
      }
      
      const std::size_t index = ofRandom(0, arr.size());
      col = arr[index];
    } else {
      // ランダムな位置に落下させる
      col = ofRandom(0, column_);
    }
  
    ofVec2f startOffset;
    startOffset.y += g_local->Height();
  
    spawnNextBrcik(col, startOffset, spawnTime_, fallTime_, curve_);
  }
  
  // ==================================================================
  // 仲間の生成
  if (cspDeltaTime_ > cspInterval_) {
    
    // ランダムな行を見つける
    std::size_t col = ofRandom(0, column_);
    
    if (auto actor = bricks_[col].back().lock()) {
      auto p_brick = dynamic_pointer_cast<Brick>(actor);
      
      // 落下中のBrickの位置に出現させない
      if (!p_brick->isAnimating()) {
        createCsp(col);
        cspDeltaTime_ = 0;
      }
    }
  }
}

void BrickManager::draw() {}

void BrickManager::gui() {
  if (ImGui::BeginMenu("BrickManager")) {
    ImGui::SliderFloat("Interval",    &spawnInterval_, 0,   3);
    ImGui::SliderFloat("Fall Time",   &fallTime_,      0,   3);
    ImGui::SliderFloat("SpawnTime",   &spawnTime_,     0,   3);
    ImGui::SliderFloat("CspInterval", &cspInterval_,   0, 120);
    ImGui::EndMenu();
  }
}

void BrickManager::createBrick(std::size_t col, float posY) {
  shared_ptr<Brick> brick = make_shared<Brick>();
  brick->setPos(ofVec2f(col * brickSize_.x, posY));
  brick->setSize(brickSize_);
  
  AddActor(brick);
  bricks_[col].emplace_back(std::move(brick));
}

void BrickManager::createNextBrick(std::size_t col) {
  // 配列にBrickが無い場合エラー
  if (bricks_[col].empty()) {
    return;
  }
  
  // 配列のケツにBrick追加
  if (auto actor = bricks_[col].back().lock()) {
    auto p_brick = dynamic_pointer_cast<Brick>(actor);
    ofVec2f pos(col * brickSize_.x, p_brick->getFallPos().y + brickSize_.y);
    
    shared_ptr<Brick> brick = make_shared<Brick>();
    brick->setPos(pos);
    brick->setSize(brickSize_);
    
    AddActor(brick);
  }
}

void BrickManager::spawnBrick(std::size_t col, float posY,
                const ofVec2f& startOffset, float spwTime,
                float fallTime, AnimCurve curve)
{
  shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
  ofVec2f pos (col * brickSize_.x, posY);
  
  spw->setSpawnTime(spwTime);
  spw->setPos(pos);
  spw->setSize(brickSize_);
  spw->set(startOffset, curve, fallTime);
  
  bricks_[col].emplace_back(spw->getActor());
  AddActor(spw);
}

void BrickManager::spawnNextBrcik(std::size_t col, const ofVec2f& startOffset,
                                  float spwTime, float fallTime,
                                  AnimCurve curve)
{
  // 配列にBrickが無い場合エラー
  if (bricks_[col].empty()) {
    return;
  }
  
  // 配列のケツにBrick追加
  if (auto actor = bricks_[col].back().lock()) {
    auto p_brick = dynamic_pointer_cast<Brick>(actor);
    
    shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
    ofVec2f pos(col * brickSize_.x, p_brick->getFallPos().y + brickSize_.y);
    
    spw->setSpawnTime(spwTime);
    spw->setPos(pos);
    spw->setSize(brickSize_);
    spw->set(startOffset, curve, fallTime);
    
    bricks_[col].emplace_back(spw->getActor());
    AddActor(spw);
  }
}

void BrickManager::createCsp(std::size_t col) {
  if (auto actor = bricks_[col].back().lock()) {
    auto p_brick = dynamic_pointer_cast<Brick>(actor);

    auto csp = make_shared<Conspecies>();
  
    ofVec2f pos(col * brickSize_.x, p_brick->getFallPos().y + brickSize_.y);
    
    // 適当な色で生成
    ofColor color(ofRandom(100, 255), // red
                  ofRandom(100, 255), // green
                  ofRandom(100, 255), // blue
                  255);               // alpha
  
    csp->setPos(pos);
    csp->setSize(brickSize_);
    csp->setColor(color);
  
    AddActor(csp);
  }
}

float BrickManager::getInterval()    const { return spawnInterval_;  }
float BrickManager::getSpawnTime()   const { return spawnTime_; }
float BrickManager::getFallTime()    const { return fallTime_;  }
float BrickManager::getCspInterval() const { return cspInterval_; }

// マイナス値はあり得ないのでmaxでセーフティーをかける
void BrickManager::setInterval(float interval)    { spawnInterval_  = max(0.0f, interval); }
void BrickManager::setSpawnTime(float time)       { spawnTime_      = max(0.0f,     time); }
void BrickManager::setFallTime(float time)        { fallTime_       = max(0.0f,     time); }
void BrickManager::setCspInterval(float interval) { cspInterval_    = max(0.0f, interval); }
