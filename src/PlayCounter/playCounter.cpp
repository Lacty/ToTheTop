
/**
 * @file   playCounter.cpp
 *
 * @author y.akira
 * @date   2017.01.25
 */

#include "precompiled.h"


//! プレイ回数をカウント
void IncPlayCounter() {
  auto path = "playCount.json";

  ofxJSON json;
  json.open(path);
  
  json["PlayCount"] = (json["PlayCount"].asInt() + 1);
  
  json.save(path);
}

//! プレイ回数を取得
int GetPlayCounter() {
  auto path = "playCount.json";
  
  ofxJSON json;
  json.open(path);
  
  return json["PlayCount"].asInt();
}
