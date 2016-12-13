﻿
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

Actor::Actor() :
  uid_(uniqueId()),
  name_("NoName"),
  finishSetup_(false),
  enableUpdate_(false),
  enableCollision_(false),
  isDead_(false) {}

// ---------------------------------------------------------------------
//
//! updateを有効にする
void Actor::enableUpdate()    { enableUpdate_    = true; }
//! 当たり判定を有効にする
void Actor::enableCollision() { enableCollision_ = true; }

// ---------------------------------------------------------------------
//
//! この関数を呼べばactorManagerから消滅する
void Actor::destroy()         { isDead_ = true;  }
//! このアクターが死んでいるかどうか
bool Actor::isDead()          { return isDead_;  }

//! setupを実行し終わったか
bool Actor::hasSetup() {
  if (finishSetup_) return true;
  finishSetup_ = true;
  return false;
}
//! updateを実行させるか
bool Actor::shouldUpdate()    { return enableUpdate_;    }
//! 当たり判定を実行するか
bool Actor::shouldCollision() { return enableCollision_; }

// ---------------------------------------------------------------------
// Setter
void Actor::setName(const string &name)  { name_ = name; }
void Actor::setTag(const int tag)        { tag_  = tag;  }
void Actor::setPos(const ofVec3f &pos)   { pos_  = pos;  }
void Actor::setVel(const ofVec3f &vel)   { vel_  = vel;  }
void Actor::setSize(const ofVec3f &size) { size_ = size; }
void Actor::setColor(const ofFloatColor &color) { color_ = color; }

// ---------------------------------------------------------------------
// Getter
const string&       Actor::getName()  const { return name_;  }
const int           Actor::getTag()   const { return tag_;   }
const ofVec3f&      Actor::getPos()   const { return pos_;   }
const ofVec3f&      Actor::getVel()   const { return vel_;   }
const ofVec3f&      Actor::getSize()  const { return size_;  }
const ofFloatColor& Actor::getColor() const { return color_; }

const ofRectangle&  Actor::getRectangle() {
  rect_.set(pos_, pos_ + size_);
  return rect_;
}
