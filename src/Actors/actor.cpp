
/**
 * @file   actor.h
 * @brief  ゲームに存在するオブジェクトの基底クラスが記述されてます
 *
 * @author y.akira
 * @date   2016.12.14
 */

#include "precompiled.h"


// ---------------------------------------------------------------------
// 固有識別id

//! カウンター用グローバル変数
uintmax_t g_uniqueIdCounter = 0;
uintmax_t Actor::uniqueId() {
  // return してからカウンターを増やす
  return g_uniqueIdCounter++;
}

/**
 * @brief アクターのコンストラクタ
 *        メンバ変数の初期化をしています
 */
Actor::Actor() :
  uid_(uniqueId()),
  name_("NoName"),
  finishSetup_(false),
  enableUpdate_(false),
  enableCollision_(false),
  isDead_(false) {}

// ---------------------------------------------------------------------
//
void Actor::enableUpdate()     { enableUpdate_    = true; }
void Actor::disableUpdate()    { enableUpdate_    = false; }
void Actor::enableCollision()  { enableCollision_ = true; }
void Actor::disableCollision() { enableCollision_ = false; }

// ---------------------------------------------------------------------
//
void Actor::destroy()         { isDead_ = true;  }
bool Actor::isDead()          { return isDead_;  }

bool Actor::hasSetup() {
  if (finishSetup_) return true;
  finishSetup_ = true;
  return false;
}
bool Actor::shouldUpdate()    { return enableUpdate_;    }
bool Actor::shouldCollision() { return enableCollision_; }

// ---------------------------------------------------------------------
// Setter
/**
 * @brief 名前を設定する
 * @param [in] name 登録する名前
 */
void Actor::setName(const string &name)  { name_ = name; }
/**
 * @brief タグを設定する
 * @param [in] tag 設定するタグ
 */
void Actor::setTag(const int tag)        { tag_  = tag;  }
/**
 * @brief 位置を設定する
 * @param [in] pos 設定する位置
 */
void Actor::setPos(const ofVec3f &pos)   { pos_  = pos;  }
/**
 * @brief 加速度を設定する
 * @param [in] vel 設定する加速度
 */
void Actor::setVel(const ofVec3f &vel)   { vel_  = vel;  }
/**
 * @brief サイズを設定する
 * @param [in] size 設定するサイズ
 */
void Actor::setSize(const ofVec3f &size) { size_ = size; }
/**
 * @brief 色を設定する
 * @param [in] color 設定する色
 */
void Actor::setColor(const ofFloatColor &color) { color_ = color; }

// ---------------------------------------------------------------------
// Getter
//! 名前を返します
const string&       Actor::getName()  const { return name_;  }
//! タグを返します
const int           Actor::getTag()   const { return tag_;   }
//! 位置を返します
const ofVec3f&      Actor::getPos()   const { return pos_;   }
//! 加速度を返します
const ofVec3f&      Actor::getVel()   const { return vel_;   }
//! サイズを返します
const ofVec3f&      Actor::getSize()  const { return size_;  }
//! 色を返します
const ofFloatColor& Actor::getColor() const { return color_; }

//! 位置とサイズから判定用矩形を生成し、返します
const ofRectangle&  Actor::getRectangle() {
  rect_.set(pos_, pos_ + size_);
  return rect_;
}
