
/**
* @file   skillState.h
* @brief  �X�L�����
*
* @author wem
* @date   2016.1.2
*/

#include "precompiled.h"


void SkillState::setup(Player* player) {
  circle_ = 100;
  telePos_ = player->getPos();
  teleSize_ = player->getSize();
  moveSpeed_ = 1.0f;
}

void SkillState::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {
  if (input.isRelease(Input::Y)) {
    player->setPos(telePos_);
    stateMgr->pop();
  }
}

void SkillState::update(float deltaTime, Player* player, ofxJoystick& input) {
  telePos_ += teleVel_;
  moveTelePos(input);
}

void SkillState::draw(Player* player) {
  auto p_pos = player->getPos();
  auto p_size = player->getSize();

  // �X�L���̗L���͈͂�Playe�̒��S����~�ŕ\��
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawCircle((p_pos + (p_size / 2)), circle_);
  ofPopMatrix();
  ofPopStyle();

  // �ړ�����l�p�`�ŕ\��
  ofPushStyle();
  ofPushMatrix();
  ofNoFill();
  ofSetColor(255, 255, 255);
  ofDrawPlane(telePos_.x + teleSize_.x/2,
              telePos_.y + teleSize_.y,
              teleSize_.x, teleSize_.y);
  ofPopMatrix();
  ofPopStyle();
}


/**
 * @brief Brick�Ƃ̓����蔻�肪�Ȃ��Ɨ�������̂ŁA�����ɂ�Brick���ђʂ��Ȃ�������ǉ�
 * @note  Player��Actor�ɒׂ��ꂽ�ꍇ�̏����͕s���Ȃ̂Ō���ǉ����܂��B
 */
void SkillState::onCollision(Player* player, Actor* c_actor) {
  auto p_pos = player->getPos();
  auto p_vel = player->getVel();
  auto p_size = player->getSize();
  auto c_pos = c_actor->getPos();
  auto c_size = c_actor->getSize();

  // Actor�ɏォ��Ԃ�����������x���O��(���E�ւ̈ړ��ʂ͂��̂܂�)
  // Actor�̏��Player�̈ʒu���C��
  if (p_pos.y < c_pos.y + c_size.y &&
    p_pos.y + p_size.y > c_pos.y + c_size.y &&
    p_pos.x < c_pos.x + c_size.x &&
    p_pos.x + p_size.x > c_pos.x &&
    p_vel.y < 0) {
    player->onFloor(true);
    player->setVel(ofVec2f(p_vel.x, 0.0f));
    player->setPos(ofVec2f(p_pos.x, c_pos.y + c_size.y));
  }
}

void SkillState::moveTelePos(ofxJoystick& input) {
  // ���E�ւ̈ړ�
  if (input.isPushing(Input::Left)) {
    teleVel_.x = -moveSpeed_;
  }
  else if (input.isPushing(Input::Right)) {
    teleVel_.x = moveSpeed_;
  }
  else {
    teleVel_.x = 0.0f;
  }

  // �㉺�ւ̈ړ�
  if (input.isPushing(Input::Down)) {
    teleVel_.y = -moveSpeed_;
  }
  else if (input.isPushing(Input::Up)) {
    teleVel_.y = moveSpeed_;
  }
  else {
    teleVel_.y = 0.0f;
  }
}
