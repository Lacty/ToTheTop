
/**
* @file   particle.h
* @brief  �p�[�e�B�N��
*
* @author wem
* @date   2017.1.21
*/

#pragma once


//! @brief Player���W�����v�����ۂȂǂɕ\������p�[�e�B�N����`�悷��N���X
class Particle{
private:
  ofVec2f pos_;
  ofColor color_;
  ofVec2f size_;
  ofVec2f vel_;

  float   limit_;  ///< �`�掞�Ԃ̏��
  float   timer_;  ///< �`��o�ߎ���

public:
  Particle();
  ~Particle() {}

  void  update(float deltaTime);
  void  draw();

  bool timeup();   ///< �^�C�}�[�����~�b�g���I�[�o�[��������Ԃ�

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
