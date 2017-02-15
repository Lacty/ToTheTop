
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
 , currentRescue_ ( 0   )
 , shouldDrawCurrentScore_( false )
{
  name_ = "uiScoreRank";
  tag_  =  SCORE_RANK;
  color_ = ofColor(200, 200, 200);

  tex_.load("Texture/conspecies.png");
  texColor_ = ofColor::white - color_;

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
  resultFont_.load(json["FontPath"].asString(), fontSize * 1.7f);
  optionFont_.load(json["FontPath"].asString(), fontSize * 0.7f);

  title_ = json["Title"].asString();
  
  playOnces_.resize(RANK_MAX);

  for (int i = 0; i < RANK_MAX; i++) {
    isStartAnim_[i] = false;
    playOnces_[i] = false;
  }
}

void uiScoreRank::setup() {
  // スコア読み込み
  auto list = GetScoreList();
  list.emplace_back(currentScore_ + (currentRescue_ * 100), currentRescue_);
  SaveScoreList(list);

  scores_ = GetScoreList();
  
  ofxJSON playerJson;
  playerJson.open("Actor/player.json");
  round_ = playerJson["Round"].asFloat();

  // 色をパターン化して、配列に格納
  ofxJSON json;
  json.open("Actor/brickManager.json");
  int colorVal = json["Color"].size();
  vector<ofColor> col(colorVal / 3);
  for (int i = 0; i < col.size(); i++) {
    col[i] = ofColor(json["Color"][i * 3].asInt(),
      json["Color"][i * 3 + 1].asInt(),
      json["Color"][i * 3 + 2].asInt());
    colors_.emplace_back(col[i]);
  }

  enableUpdate();
}

void uiScoreRank::update(float deltaTime) {
  deltaTime_ += deltaTime;
  
  int index = min(int(deltaTime_ / animTimeOffset_), RANK_MAX);
  if (index < RANK_MAX) {
    if (!isStartAnim_[index]) {
      animXs_[index].animateFromTo(posXs_[index], 0);
      animXs_[index].setDuration(animTime_);
      animXs_[index].setCurve(curve_);
      isStartAnim_[index] = true;
    }
  }
  
  for (int i = 0; i < index; i++) {
    if (!animXs_[i].isAnimating()) { continue; }
    if (!playOnces_[i]) {
      PlaySound(SLIDE_SCORE);
      playOnces_[i] = true;
    }
    animXs_[i].update(deltaTime);
    posXs_[i] = animXs_[i];
  }
}

void uiScoreRank::draw() {
  ofPushStyle();
  ofPushMatrix();

  ofSetColor(color_);
  ofTranslate(pos_);

  // 現在のスコア描画
  if (shouldDrawCurrentScore_) {
    string lstr = "Result";
    float w = font_.stringWidth(lstr);
    float h = font_.stringHeight(lstr);
    font_.drawString(lstr, -w * 0.5, -h * 8);

    // 最終スコア表示
    string str = ofToString(currentScore_ + (currentRescue_ * 100));
    w   = resultFont_.stringWidth(str);
    h   = resultFont_.stringHeight(str);
    resultFont_.drawString(str, -w * 0.5, -h * 3);

    // スコアの内訳
    string rstr = ofToString(currentScore_) + " + " + "  (100) x " + ofToString(currentRescue_);
    w = optionFont_.stringWidth(rstr);
    h = optionFont_.stringHeight(rstr);
    optionFont_.drawString(rstr, -w * 0.5, -h * 4);

    // スコアの桁に合わせてアイコンの位置を修正
    float cwp = 0.0f;
    // スコア：0～999 && 救助：0～9
    if (currentScore_ < 1000 && currentRescue_ < 10) { cwp = 0.17f; }
    // スコア：1000～9999 && 救助：0～9
    else if (currentScore_ >= 1000 && currentScore_ < 10000 && currentRescue_ < 10) { cwp = 0.14f; }
    // スコア：1000～9999 && 救助：10～99
    else if (currentScore_ >= 1000 && currentScore_ < 10000 && currentRescue_ >= 10 && currentRescue_ < 100) { cwp = 0.14f; }
    // スコア：10000～ && 救助：10～99
    else if (currentScore_ >= 10000 && currentRescue_ >= 10 && currentRescue_ < 100) { cwp = 0.12f; }
    // スコア10000 && 救助：100
    else { cwp = 0.14f; }

    // 仲間アイコン(外枠)
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofVec2f(-w * cwp, -h * 4.8));
    ofDrawRectRounded(ofVec2f(0, 0), w / 10, w / 10, round_/2);
    ofPopStyle();
    ofPopMatrix();
    // 仲間アイコン(顔文字)
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofVec2f(-w * cwp, -h * 4.8));
    ofSetColor(texColor_);
    tex_.draw(0, 0, w / 10, w / 10);
    ofPopStyle();
    ofPopMatrix();
  }
  
  // タイトルの描画
  float w = font_.stringWidth(title_);
  font_.drawString(title_, -w * 0.5, 0);

  // 文字の縦幅を算出
  float height = font_.stringHeight("N");

  for (int i = 0; i < RANK_MAX; i++) {
    // アニメーション待機中は描画しない
    if (!isStartAnim_[i]) { continue; }
    
    // データがなければ "None"
    auto str = i < scores_.size() ? ofToString(scores_[i].score) : "None";
    auto y   = (i + 1) * height + (i + 1) * yOffset_;
    
    // 順位をつける 1st, 2nd...
    auto offset = "  ";
    str = db_[i] + offset + str;
    w = font_.stringWidth(db_[i] + offset);
    
    // ランキングに今回のスコアと同じ数値があれば色を変更させる
    if (scores_[i].score == currentScore_ + (currentRescue_ * 100)) {
      ofPushStyle();
      auto i = ofRandom(0, colors_.size());
      ofSetColor(colors_[i]);
    }

    font_.drawString(str, float(animXs_[i]) - w, y);

    if (scores_[i].score == currentScore_ + (currentRescue_ * 100)) {
      ofPopStyle();
    }
  }
  
  ofPopMatrix();
  ofPopStyle();
}

void uiScoreRank::gui() {}

void uiScoreRank::enableDrawCurrentScore()     { shouldDrawCurrentScore_ = true;  }
void uiScoreRank::disableDrawCurrentScore()    { shouldDrawCurrentScore_ = false; }

void uiScoreRank::setCurrentScore(int score)   { currentScore_ = score; }
void uiScoreRank::setCurrentRescue(int rescue) { currentRescue_ = rescue; }
