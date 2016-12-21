
/**
 * @file     backGround.h
 * @brief    背景
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#pragma once


class Star;

/**
 * @brief 宇宙をテーマにした背景を描画するクラス
 */
class BackGround {
private:
  float interval_;
  float deltaTime_;
  
  ofFloatColor inColor_;
  ofFloatColor outColor_;

  ofVec2f windowSize_;
  
  vector<unique_ptr<Star>> stars_;
  ofFloatColor starColor_;
  
  // windowのサイズが変わった際に呼ばれる関数
  void windowResizeCallback(ofResizeEventArgs &resize);
  
  void gui();
  
public:
  BackGround();
  ~BackGround() {}
  
  void setup();
  void update(float deltaTime);
  void draw();
};


class Star {
private:
  ofVec3f pos_;
  ofVec3f vel_;
  
  float   extend_;  ///< 時間経過で伸びる速度(height)
  float   shrink_;  ///< 時間経過で縮む速度(width)
  
  float   clause_;  ///< heightに対して節目がどこにあるか(0~1)
  float   width_;
  float   height_;
  
  ofFloatColor color_;
  
public:
  Star(const ofVec3f& pos,
       const ofVec3f& vel,
       const ofFloatColor& color,
       float extend,
       float shrink,
       float clause,
       float width,
       float height);
  
  void update(float deltaTime);
  void draw();
};
