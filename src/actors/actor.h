
#pragma once
#include "ofMain.h"


// ゲームに存在するオブジェクトの基底クラス
// 位置やサイズ、色などの基本的な情報を持つ
class Actor {
protected:
  string name_;
  int    tag_;
  
  ofVec3f pos_;
  ofVec3f vel_;
  ofVec3f size_;
  
  ofColor color_;
  
  ofRectangle rect_;
  
public:
  Actor() {}
  virtual ~Actor() {}
  
  virtual void setup() {}
  virtual void update(float deltaTime) {}
  virtual void draw() {}
  
  string&  name()  { return name_;  }
  int&     tag()   { return tag_;   }
  ofVec3f& pos()   { return pos_;   }
  ofVec3f& vel()   { return vel_;   }
  ofVec3f& size()  { return size_;  }
  ofColor& color() { return color_; }
  
  ofRectangle& rectangle() {
    rect_.set(pos_, pos_ + size_);
    return rect_;
  }
};
