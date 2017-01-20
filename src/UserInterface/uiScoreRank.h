
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
  
  float                       yOffset_;
  
  float                       deltaTime_;
  float                       animTime_;
  float                       animTimeOffset_;
  
  float                       currentScore_;
  bool                        shouldDrawCurrentScore_;
  
  vector<score_t>             scores_;
  
  ofTrueTypeFont              font_;
  string                      title_;

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
};
