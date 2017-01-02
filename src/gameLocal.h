
/**
 * @file   gameLocal.h
 * @brief  共通で使用するものを置いている
 *
 * @author y.akria
 * @date   2017.01.02
 */

#pragma once


class GameLocal {
private:
  int width_;
  int height_;
  
  float lastFrame_;
  float frameAcc_;
  
  void update(ofEventArgs &args);
  void windowResized(ofResizeEventArgs &resize);
  
public:
  GameLocal();
  ~GameLocal() {}

  void    Setup();                 ///< このクラスの初期化

  int     Width() const;           ///< ウィンドウの横幅を返す
  int     Height() const;          ///< ウィンドウの縦幅を返す
  
  float   LastFrame() const;       ///< 前のフレームから現在にかけてかかった時間を返す
  float   FrameAcc() const;        ///< ゲーム内時間の加速度 デフォルト 1
  
  void    SetFrameAcc(float acc);  ///< ゲーム内時間の加速度を設定
};

//! GameLocalへのアクセスはこの変数を介す
extern unique_ptr<GameLocal> g_local;
