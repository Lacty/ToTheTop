
/**
 * @file     uiRank.h
 * @brief    UI ランク表示
 *
 * @author   y.akira
 * @date     2017/01/18
 */

#include "precompiled.h"


uiScoreRank::uiScoreRank()
 : RANK_MAX       ( 5   )
 , curve_         ( AnimCurve::EASE_IN_EASE_OUT )
 , yOffset_       ( 50  )
 , deltaTime_     ( 0   )
 , animTime_      ( 1   )
 , animTimeOffset_( 0.2 )
 , currentScore_  ( 0   )
 , shouldDrawCurrentScore_( false )
{
  name_ = "uiScoreRank";
  tag_  =  SCORE_RANK;
  
  ofxJSON json;
  json.open("UI/scoreRank.json");
  
  RANK_MAX = json["RankMax"].asInt();
  
  isStartAnim_.resize(RANK_MAX);
  animXs_.resize(RANK_MAX);
  posXs_.resize(RANK_MAX);
  for (auto& x : posXs_)
    { x = g_local->Width(); }
  
  db_ = vector<string> {
    "1st", "2nd", "3rd", "4th", "5th",
    "6th", "7th", "8th", "9th", "10th"
  };
  
  // Jsonからデータ読み込み
  RANK_MAX        = json["RankMax"].asInt();
  curve_          = AnimCurve(json["Curve"].asInt());
  yOffset_        = json["yOffset"].asFloat();
  animTime_       = json["AnimTime"].asFloat();
  animTimeOffset_ = json["AnimTimeOffset"].asFloat();
  int fontSize    = g_local->Width() * json["FontSize"].asFloat();
  pos_.set(g_local->Width()  * json["Pos"][0].asFloat(),
           g_local->Height() * json["Pos"][1].asFloat());
  
  font_.load(json["FontPath"].asString(), fontSize);
  
  title_ = json["Title"].asString();
  
  for (int i = 0; i < RANK_MAX; i++) {
    isStartAnim_[i] = false;
  }
}

void uiScoreRank::setup() {
  // スコア読み込み
  scores_ = GetScoreList();
  
  enableUpdate();
}

void uiScoreRank::update(float deltaTime) {
  deltaTime_ += deltaTime;
  
  int index = min(int(deltaTime_ / animTimeOffset_), RANK_MAX);
  if (index <= RANK_MAX) {
    if (!isStartAnim_[index]) {
      animXs_[index].animateFromTo(posXs_[index], 0);
      animXs_[index].setDuration(animTime_);
      animXs_[index].setCurve(curve_);
      isStartAnim_[index] = true;
    }
  }
  
  for (int i = 0; i < index; i++) {
    if (!animXs_[i].isAnimating()) { continue; }
    animXs_[i].update(deltaTime);
    posXs_[i] = animXs_[i];
  }
}

void uiScoreRank::draw() {
  ofPushMatrix();
  ofTranslate(pos_);
  
  // 現在のスコア描画
  if (shouldDrawCurrentScore_) {
    string str = "Score : " + ofToString(currentScore_);
    float  w   = font_.stringWidth(str);
    float  h   = font_.stringHeight(str);
    font_.drawString(str, -w * 0.5, -h * 3);
  }
  
  // タイトルの描画
  float w = font_.stringWidth(title_);
  font_.drawString(title_, -w * 0.5, 0);

  // 文字の縦幅を算出
  float height = font_.stringHeight("N");

  for (int i = 0; i < RANK_MAX; i++) {
    // アニメーション待機中は描画しない
    if (!isStartAnim_[i]) { continue; }
    
    auto str = ofToString(scores_[i].score);
    auto y   = (i + 1) * height + (i + 1) * yOffset_;
    
    // データがなければ "None"
    str = (i < scores_.size()) ? str : "None";
    
    // 順位をつける 1st, 2nd...
    auto offset = "  ";
    str = db_[i] + offset + str;
    w = font_.stringWidth(db_[i] + offset);
    
    font_.drawString(str, float(animXs_[i]) - w, y);
  }
  
  ofPopMatrix();
}

void uiScoreRank::gui() {}

void uiScoreRank::enableDrawCurrentScore()  { shouldDrawCurrentScore_ = true;  }
void uiScoreRank::disableDrawCurrentScore() { shouldDrawCurrentScore_ = false; }

void uiScoreRank::setCurrentScore(int score) { currentScore_ = score; }
