
/**
* @file   particleManager.h
* @brief  �p�[�e�B�N���}�l�[�W���[
*
* @author wem
* @date   2017.1.22
*/

#pragma once


class Particle;

class ParticleManager {
private:
  list<Particle> particles_;
  ofVec2f pos_;
  ofColor color_;
  bool    isGenerat_;   ///< �����X�C�b�`

  // ��������p�[�e�B�N���ɗ^����l��ǂݍ���ł���
  ofVec2f sizeMin_;
  ofVec2f sizeMax_;
  ofVec2f velMin_;
  ofVec2f velMax_;
  float   limit_;

public:
  ParticleManager();
  ~ParticleManager() {}

  void setup();
  void update(float deltaTime);
  void draw();
  void gui();

  void isGenerat(bool g);
  bool isGenerat();
  void setPos(ofVec2f pos);
  void setColor(ofColor color);
};

inline void ParticleManager::isGenerat(bool g)       { isGenerat_ = g; }
inline bool ParticleManager::isGenerat()             { return isGenerat_; }

inline void ParticleManager::setPos(ofVec2f pos)     { pos_ = pos; }
inline void ParticleManager::setColor(ofColor color) { color_ = color; }
