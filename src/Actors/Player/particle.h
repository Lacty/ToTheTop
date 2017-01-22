
/**
* @file   particle.h
* @brief  パーティクル
*
* @author wem
* @date   2017.1.21
*/

#pragma once


//! @brief Playerがジャンプした際などに表示するパーティクルを描画するクラス
class Particle{
private:
  ofVec2f pos_;
  ofColor color_;
  ofVec2f size_;
  ofVec2f vel_;

  float   limit_;  ///< 描画時間の上限
  float   timer_;  ///< 描画経過時間

public:
  Particle();
  ~Particle() {}

  void  update(float deltaTime);
  void  draw();

  bool timeup();   ///< タイマーがリミットをオーバーしたかを返す

  //--------------------------------
  // Setter
  void setPos(ofVec2f pos);
  void setSize(ofVec2f size);
  void setVel(ofVec2f vel);
  void setColor(ofColor col);
  void setLimit(float limit);

  //--------------------------------
  // Getter
  ofVec2f getPos();
  ofVec2f getSize();
  ofVec2f getVel();
};

inline void Particle::setPos(ofVec2f pos)     { pos_ = pos;     }
inline void Particle::setSize(ofVec2f size)   { size_ = size;   }
inline void Particle::setVel(ofVec2f vel)     { vel_ = vel;     }
inline void Particle::setColor(ofColor color) { color_ = color; }
inline void Particle::setLimit(float limit)   { limit_ = limit; }

inline ofVec2f Particle::getPos()   { return pos_;   }
inline ofVec2f Particle::getSize()  { return size_;  }
inline ofVec2f Particle::getVel()   { return vel_;   }
