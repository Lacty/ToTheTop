
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

  // 色をパターン化して、配列に格納
  int colorVal = json["Color"].size();
  vector<ofColor> col(colorVal/3);
  for (int i = 0; i < col.size(); i++) {
    col[i] = ofColor(json["Color"][i*3].asInt(),
                     json["Color"][i*3+1].asInt(), 
                     json["Color"][i*3+2].asInt());
    cspColors_.emplace_back(col[i]);
  }
}

void BrickManager::setup() {
  enableUpdate();
}

void BrickManager::update(float deltaTime) {
  if (!player_.lock()) {
    player_ = dynamic_pointer_cast<Player>(FindActor(PLAYER));
    return;
  }

  if (!player_.lock()->isDead()) {
    updateCreate(deltaTime);
    updateDelete(deltaTime);
  }
}

void BrickManager::draw() {}

void BrickManager::gui() {
  if (ImGui::BeginMenu("BrickManager")) {
    
    for (const auto& bricks : bricks_) {
      num_ += bricks.size();
    }
    ImGui::Text("Num : %i", num_);
    
    ImGui::SliderFloat("Interval",    &spawnInterval_, 0,   3);
    ImGui::SliderFloat("Fall Time",   &fallTime_,      0,   3);
    ImGui::SliderFloat("SpawnTime",   &spawnTime_,     0,   3);
    ImGui::SliderFloat("CspInterval", &cspInterval_,   0, 120);
    ImGui::EndMenu();
  
    num_ = 0;
  }
}

void BrickManager::updateCreate(float deltaTime) {
  deltaTime_    += deltaTime;
  cspDeltaTime_ += deltaTime;
  
  // ==============================================================
  // Brickの生成
  if (deltaTime_ > spawnInterval_) {
    deltaTime_ = 0;
    
    shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
    
    int high = 0;
    int low  = bricks_[0].size();
    for (int i = 0; i < column_; i++) {
      high = max(int(bricks_[i].size()), high);
      low  = min(int(bricks_[i].size()), low);
    }
    
    int col;
    
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

void BrickManager::updateDelete(float deltaTime) {
  float hight = 0;
  
  // 一番高い位置にあるBrickのyを求める
  for (const auto& bricks : bricks_) {
    for (const auto& brick : bricks) {
      if (auto b = brick.lock()) {
        hight = max(b->getPos().y, hight);
      }
    }
  }
  
  // 0だったらBrickが存在しないので処理をしない
  if (!hight) return;
  
  // 画面の高さ＊２以上離れたBrickは削除対象にする
  float limit = hight - g_local->Height() * 2;
  for (const auto& bricks : bricks_) {
    for (const auto& brick : bricks) {
      if (auto b = brick.lock()) {
        if (b->getPos().y < limit) {
          b->destroy();
        }
      }
    }
  }
  
  // 削除対象になったBrickを監視から外す
  for (auto& bricks : bricks_) {
    bricks.remove_if(
      [] (const weak_ptr<Actor>& wp)->bool {
        if (auto p = wp.lock()) {
          return p->shouldDestroy();
        } else {
          return true;
        }
      }
    );
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

    // setupで登録したカラーバリエーションからランダム選択
    ofColor color = cspColors_[ofRandom(0, cspColors_.size()-1)];
  
    // Brickの半分のサイズで仲間を表示し、座標はBrickの真ん中に来るように調整
    csp->setPos(ofVec2f(pos.x + (brickSize_.x/4), pos.y));
    csp->setSize(brickSize_/2);
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
