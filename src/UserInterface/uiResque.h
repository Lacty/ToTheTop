
/**
* @file     uiResque.h
* @brief    UI 救出数
*
* @author   wem
* @date     2017.2.13
*/

#pragma once


class Actor;

class uiResque : public uiBase {
private:
  int                num_;
  int                currentNum_;

  int w_, h_;                           ///< デフォルトの画面サイズを保存
  float wRatio_, hRatio_;               ///< 変更前後の画面倍率
  float round_;

  ofImage            tex_;
  ofFloatColor       texColor_; 
  ofVec2f            iconSize_;
  ofVec2f            iconPos_;
  
  float              scale_;
  float              scaleMax_;
  float              scaleSpeed_;

  float              camY_;
  ofVec2f            offset_;

  ofTrueTypeFont     font_;

public:
  uiResque();
  virtual ~uiResque() {}

  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;

  void setCamY(float y);

  void setNum(float num);
  const int getNum() const;
};
