
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

public:
  uiScoreRank();
  virtual ~uiScoreRank() {}
  
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
};
