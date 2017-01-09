
/**
 * @file     uiBase.cpp
 * @brief    UI
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#include "precompiled.h"


uiBase::uiBase()
  : finishSetup_  ( false    )
  , enableUpdate_ ( false    )
  , name_         ( "NoName" )
  , tag_          ( -1       )
  , isDead_       ( false    )
{}

/**
 * @brief 名前を設定する
 * @param [in] name 登録する名前
 */
void uiBase::setName(const string &name) { name_ = name; }
/**
 * @brief タグを設定する
 * @param [in] tag 設定するタグ
 */
void uiBase::setTag(const int tag)       { tag_  = tag;  }
/**
 * @brief 位置を設定する
 * @param [in] pos 設定する位置
 */
void uiBase::setPos(const ofVec3f &pos)  { pos_  = pos;  }

void uiBase::setColor(const ofColor& color) { color_ = color; }

//! 名前を返します
const string&  uiBase::getName()  const { return name_;  }
//! タグを返します
const int      uiBase::getTag()   const { return tag_;   }
//! 位置を返します
const ofVec3f& uiBase::getPos()   const { return pos_;   }
//! 色を返す
const ofColor& uiBase::getColor() const { return color_; }

void uiBase::destroy() { isDead_ = true;  }
bool uiBase::isDead()  { return isDead_;  }

void uiBase::enableUpdate()  { enableUpdate_ = true;  }
void uiBase::disableUpdate() { enableUpdate_ = false; }

bool uiBase::hasSetup() {
  if (finishSetup_) return true;
  finishSetup_ = true;
  return false;
}
bool uiBase::shouldUpdate()    { return enableUpdate_; }
