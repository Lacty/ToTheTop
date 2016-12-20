
/**
* @file   input.h
* @brief  デバイスのボタン配列を管理するクラス
*
* @author wem
* @date   2016.12.20
*/

#include "input.h"


int Input::Left  = -1;
int Input::Right = -1;
int Input::Up    = -1;
int Input::Down  = -1;
int Input::X     = -1;
int Input::Y     = -1;
int Input::A     = -1;
int Input::B     = -1;

/**
* @brief 　jsonファイルからボタン配列の読み込みをします
*/
void Input::setup(const string& path) {
  ofxJSON json;
  json.open(path);

  Left  = json["Left"].asInt();
  Right = json["Right"].asInt();
  Up    = json["Up"].asInt();
  Down  = json["Down"].asInt();
  X     = json["X"].asInt();
  Y     = json["Y"].asInt();
  A     = json["A"].asInt();
  B     = json["B"].asInt();
}
