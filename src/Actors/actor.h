﻿
#pragma once


// ゲームに存在するオブジェクトの基底クラス
// 位置やサイズ、色などの基本的な情報を持つ
class Actor {
private:
  uintmax_t    uid_;       // 固有識別id
  uintmax_t    uniqueId(); // 固有idを生成する
  
  bool         finishSetup_;
  bool         enableUpdate_;
  bool         enableCollision_;
  
protected:
  void         finishSetup();     // setupが終了した時に呼ぶ
  void         enableUpdate();    // updateを有効にする
  void         enableCollision(); // 当たり判定を有効にする
  
protected:
  string       name_;    // 名前
  int          tag_;     // タグ

  bool         isDead_;  // 生死
  
  ofVec3f      pos_;     // 位置
  ofVec3f      vel_;     // 加速度
  ofVec3f      size_;    // サイズ
  
  ofFloatColor color_;   // 色
  
  ofRectangle  rect_;    // 判定用矩形
  
public:
  Actor();
  virtual ~Actor() {}
  
  virtual void setup() {
    finishSetup();
    // updateを実行する場合はコメントを外す
    // enableUpdate();
  }
  virtual void update(float deltaTime) {}
  virtual void draw() {ofLog() << "id:" << uid_ << " draw()";}
  
  virtual void onCollisionEnter(Actor& colActor) {}
  
  // -------------------------------------------
  //
  void destroy();
  bool isDead();
  
  bool hasSetup();        // setupを実行し終わったか
  bool shouldUpdate();    // updateを実行させるか
  bool shouldCollision(); // 当たり判定を実行するか
  
  // -------------------------------------------
  // Setter
  void setName  (const string&       name);
  void setTag   (const int           tag);
  void setPos   (const ofVec3f&      pos);
  void setVel   (const ofVec3f&      vel);
  void setSize  (const ofVec3f&      size);
  void setColor (const ofFloatColor& color);
  
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
