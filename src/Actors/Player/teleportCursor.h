
/**
* @file   teleportCursor.h
* @brief  �e���|�[�g�J�[�\��(�ړ���\��)
*
* @author wem
* @date   2016.1.6
*/

#pragma once


class StateManager;

//! @brief �v���C���[�N���X
class TeleportCursor : public Actor {
private:
  ofxJoystick joy_;   ///< �Q�[���p�b�h�̓��͔�����Ƃ�

  bool  onBrick_;     ///< Brick�Ƃ̏Փ˔���
  float moveSpeed_;   ///< �ړ����x
  float reduce_;      ///< Teleport�g�p���̃X���[�{��
  float circle_;      ///< �e���|�[�g�̗L���͈͂��������~�̃T�C�Y

  float round_;       ///< �J�[�\���̊ۂ�
  ofVec2f playerPos_; ///< �v���C���[�̌��ݒn���ꎞ�ۑ�
  ofVec2f playerVel_; ///< �v���C���[�̈ړ��ʂ��ꎞ�ۑ�

  void movePos(ofxJoystick& input);
public:
  TeleportCursor();

  void  setup() override;
  void  update(float deltaTime) override;
  void  draw() override;
  void  gui()  override;


  void  setRound(float round);
  void  setOnBrick(bool o);
  void  setPlayerPos(ofVec2f p_pos);
  void  setPlayerVel(ofVec2f p_vel);

  bool  getOnBrick() const;
  float getSpeed()   const;
  float getReduce()  const;
  float getCircle()  const;

  void  onCollision(Actor* c_actor) override;
};

inline void  TeleportCursor::setRound(float r)          { round_ = r; }
inline void TeleportCursor::setOnBrick(bool o)          { onBrick_ = o; }
inline void TeleportCursor::setPlayerPos(ofVec2f p_pos) { playerPos_ = p_pos; }
inline void TeleportCursor::setPlayerVel(ofVec2f p_vel) { playerVel_ = p_vel; }

inline bool  TeleportCursor::getOnBrick() const         { return onBrick_; }
inline float TeleportCursor::getSpeed()   const         { return moveSpeed_; }
inline float TeleportCursor::getReduce()  const         { return reduce_; }
inline float TeleportCursor::getCircle()  const         { return circle_; }

