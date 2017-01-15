
/**
* @file   input.h
* @brief  デバイスのボタン配列を管理するクラス
*
* @author wem
* @date   2016.12.20
*/

#include "precompiled.h"


int Input::Left       = -1;
int Input::Right      = -1;
int Input::Up         = -1;
int Input::Down       = -1;
int Input::X          = -1;
int Input::Y          = -1;
int Input::A          = -1;
int Input::B          = -1;
int Input::LeftAxisX  = -1;
int Input::LeftAxisY  = -1;
int Input::RightAxisX = -1;
int Input::RightAxisY = -1;

/**
* @brief  デバイスのボタンの名称と番号を紐づけし、コード内で明示的に表記出来るように。
*/
void Input::setup(const string& path) {
  ofxJSON json;
  json.open(path);

  Left       = json["Left"].asInt();
  Right      = json["Right"].asInt();
  Up         = json["Up"].asInt();
  Down       = json["Down"].asInt();
  X          = json["X"].asInt();
  Y          = json["Y"].asInt();
  A          = json["A"].asInt();
  B          = json["B"].asInt();
  LeftAxisX  = json["LeftAxisX"].asInt();
  LeftAxisY  = json["LeftAxisY"].asInt();
  RightAxisX = json["RightAxisX"].asInt();
  RightAxisY = json["RightAxisY"].asInt();
}
