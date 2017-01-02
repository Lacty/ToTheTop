
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

  void Setup();

  int Width() const;
  int Height() const;
  
  float LastFrame() const;
  float FrameAcc() const;
  
  void SetFrameAcc(float acc);
};

extern unique_ptr<GameLocal> g_local;
