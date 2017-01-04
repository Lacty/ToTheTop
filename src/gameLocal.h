
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
  int     width_;
  int     height_;
  
  float   lastFrame_;
  float   frameAcc_;
  float   frameRate_;
  
  void    update(ofEventArgs &args);
  void    windowResized(ofResizeEventArgs &resize);
  
public:
  GameLocal();
  ~GameLocal() {}

  void    Setup();                 ///< このクラスの初期化

  bool    Stop;

  int     Width() const;           ///< ウィンドウの横幅を返す
  int     Height() const;          ///< ウィンドウの縦幅を返す
  
  int     HalfWidth() const;       ///< ウィンドウの半分の横幅を返す
  int     HalfHeight() const;      ///< ウィンドウの半分の縦幅を返す
  
  ofVec2f WindowSize() const;      ///< ウィンドウのサイズを返す
  ofVec2f WindowHalfSize() const;  ///< ウィンドウの半分のサイズを返す
  
  float   LastFrame() const;       ///< 前のフレームから現在にかけてかかった時間を返す
  float   AccedLastFrame() const;  ///< ゲーム内時間でのLastFrameを返す
  float   FrameAcc() const;        ///< ゲーム内時間の加速度 デフォルト 1
  float   FrameRate() const;       ///< フレームレートを返します 処理落ちがなければ基本６０
  
  void    SetFrameAcc(float acc);  ///< ゲーム内時間の加速度を設定
};

//! GameLocalへのアクセスはこの変数を介す
extern unique_ptr<GameLocal> g_local;
