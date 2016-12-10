
#pragma once


// ゲームに存在するオブジェクトの基底クラス
// 位置やサイズ、色などの基本的な情報を持つ
class Actor {
private:
  u_int        uid_;       // 固有識別id
  u_int        uniqueId(); // 固有idを生成する
  
protected:
  string       name_;    // 名前
  int          tag_;     // タグ

  bool         active_;  // 生死
  
  ofVec3f      pos_;     // 位置
  ofVec3f      vel_;     // 加速度
  ofVec3f      size_;    // サイズ
  
  ofFloatColor color_;   // 色
  
  ofRectangle  rect_;    // 判定用矩形
  
public:
  Actor() : uid_(uniqueId()) {}
  virtual ~Actor() {}
  
  virtual void setup() {}
  virtual void update(float deltaTime) {}
  virtual void draw() {}
  
  virtual void onCollisionEnter(Actor* colActor) {}
  
  // -------------------------------------------
  // Setter
  void setName  (const string&       name);
  void setTag   (const int           tag);
  void setPos   (const ofVec3f&      pos);
  void setVel   (const ofVec3f&      vel);
  void setSize  (const ofVec3f&      size);
  void setColor (const ofFloatColor& color);
  
  // アクティベート
  void activate(bool f = true);
  void destroy();
  bool isActive();
  
  // -------------------------------------------
  // Getter
  const string&       getName()  const;
  const int           getTag()   const;
  const ofVec3f&      getPos()   const;
  const ofVec3f&      getVel()   const;
  const ofVec3f&      getSize()  const;
  const ofFloatColor& getColor() const;
  const ofRectangle&  getRectangle();
  
  // -------------------------------------------
  // Operator
  bool operator==(const Actor& actor) const noexcept {
    return this->uid_ == actor.uid_;
  }
  
  bool operator!=(const Actor& actor) const noexcept {
    return !(*this == actor);
  }
};
