
/**
 * @file   actor.h
 * @brief  ゲームに存在するオブジェクトの基底クラスが記述されてます
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


/**
 * @brief  ゲームに存在するオブジェクトの基底クラス
 *         位置やサイズ、色などの基本的な情報を持つ
 */
class Actor {
private:
  uintmax_t    uid_;          // 固有識別id
  uintmax_t    generateUid(); // 固有idを生成する
  
  bool         finishSetup_;
  bool         enableUpdate_;
  bool         enableCollision_;
  
public:
  void         enableUpdate();     ///< updateを有効にする
  void         disableUpdate();    ///< updateを無効にする
  void         enableCollision();  ///< 当たり判定を有効にする
  void         disableCollision(); ///< 当たり判定を無効にする
  
protected:
  string       name_;    ///< 名前
  int          tag_;     ///< タグ
  bool         destroy_; ///< 生死
  bool         hide_;    ///< 表示・非表示
  ofVec3f      pos_;     ///< 位置
  ofVec3f      vel_;     ///< 加速度
  ofVec3f      size_;    ///< サイズ
  ofFloatColor color_;   ///< 色
  ofRectangle  rect_;    ///< 判定用矩形

public:
  Actor();
  virtual ~Actor() {}
  
  virtual void setup() {}
  virtual void update(float deltaTime) {}
  virtual void draw() {}
  virtual void gui() {}
  
  virtual void onCollision(Actor* c_actor) {}
  
  // -------------------------------------------
  //
  void destroy();         ///< この関数を呼べばactorManagerから消滅する
  bool shouldDestroy();   ///< このアクターをActorManagerから消すべきか
  
  bool hasSetup();        ///< setupを実行し終わったか
  bool shouldUpdate();    ///< updateを実行させるか
  bool shouldCollision(); ///< 当たり判定を実行するか
  
  void show();            ///< アクターを表示させる
  void hide();            ///< アクターを非表示にする
  bool isHide();          ///< 非表示設定かどうか
  
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
