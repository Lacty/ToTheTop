
/**
 * @file     uiRank.h
 * @brief    UI ランク表示
 *
 * @author   y.akira
 * @date     2017/01/18
 */

#pragma once


class uiScoreRank : public uiBase {
private:
  int                         RANK_MAX;

  AnimCurve                   curve_;
  vector<bool>                isStartAnim_;
  vector<ofxAnimatableFloat>  animXs_;
  vector<float>               posXs_;
  vector<string>              db_;
  
  ofImage                     tex_;
  ofFloatColor                texColor_;
  float                       round_;

  float                       yOffset_;
  
  float                       deltaTime_;
  float                       animTime_;
  float                       animTimeOffset_;
  
  float                       currentScore_;
  int                         currentRescue_;
  bool                        shouldDrawCurrentScore_;
  
  vector<score_t>             scores_;
  
  ofTrueTypeFont              font_;
  ofTrueTypeFont              resultFont_;
  ofTrueTypeFont              optionFont_;
  string                      title_;

  vector<bool>                playOnces_;

public:
  uiScoreRank();
  virtual ~uiScoreRank() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
  
  void enableDrawCurrentScore();
  void disableDrawCurrentScore();
  
  void setCurrentScore(int score);
  void setCurrentRescue(int rescue);
};
