
#include "../precompiled.h"


// ---------------------------------------------------------------------
// Setter
void Actor::setName(const string &name)  { name_ = name; }
void Actor::setTag(const int tag)        { tag_  = tag;  }
void Actor::setPos(const ofVec3f &pos)   { pos_  = pos;  }
void Actor::setVel(const ofVec3f &vel)   { vel_  = vel;  }
void Actor::setSize(const ofVec3f &size) { size_ = size; }
void Actor::setColor(const ofFloatColor &color) { color_ = color; }

// ---------------------------------------------------------------------
// アクティベート
void Actor::activate(bool f) { active_ = f;     }
void Actor::destroy()        { active_ = false; }
bool Actor::isActive()       { return active_;  }

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
