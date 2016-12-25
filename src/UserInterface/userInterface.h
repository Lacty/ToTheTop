
/**
 * @file     userInterface.h
 * @brief    UI
 *
 * @author   y.akira
 * @date     2016.12.21
 */

#pragma once


/**
 * @brief UI基底クラス
 */
class uiBase {
private:
  bool         finishSetup_;
  bool         enableUpdate_;

protected:
  string       name_;   ///< 名前
  int          tag_;    ///< タグ
  bool         isDead_; ///< 生死
  ofVec3f      pos_;    ///< 位置
  
public:
  uiBase();
  virtual ~uiBase() {}
  
  virtual void    setup() {}
  virtual void    update(float deltaTime) {}
  virtual void    draw() {}
  
  
  void            setName (const string&  name);
  void            setTag  (const int       tag);
  void            setPos  (const ofVec3f&  pos);
  
  const string&   getName() const;
  const int       getTag()  const;
  const ofVec3f&  getPos()  const;
  
  void            destroy();          ///< この関数を呼べばuiManagerから消滅する
  bool            isDead();           ///< このuiが死んでいるかどうか
  
  void            enableUpdate();     ///< updateを有効にする
  void            disableUpdate();    ///< updateを無効にする
  
  bool            hasSetup();         ///< setupを実行し終わったか
  bool            shouldUpdate();     ///< updateを実行させるか
};
