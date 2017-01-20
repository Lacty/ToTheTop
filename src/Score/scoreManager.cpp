
/**
 * @file   scoreManager.cpp
 *
 * @author y.akira
 * @date   2017.01.15
 */

#include "precompiled.h"


// すげぇわけわかんねぇ名前
// 数値の頭に'0'をくっつける関数
// i 数値, digit 桁
// IntToStrDigit(31, 4); // 0031
string IntToStrDigit(int i, int digit) {
  string str = ofToString(i);
  while(str.size() < digit) {
    str = "0" + str;
  }
  return str;
}

string g_scoreListSavePath = "Score/score.json";

vector<score_t> GetScoreList() {
  vector<score_t> list;

  // jsonから読み込み
  ofxJSON json;
  json.open(g_scoreListSavePath);
  if (!json) {
    assert(json);                   // debug   : err
    json.save(g_scoreListSavePath); // release : create file
    return list;                    // 何もない配列を返す
  }
  
  auto names = json["Score"].getMemberNames();
  
  // 配列確保
  list.resize(json["Score"].size());
  
  // 読み込んだデータを配列に移す
  int i = 0;
  for (auto& itr : list) {
    auto j = json["Score"][names[i]];
    
    itr.score  = j["score"].asInt();  // スコア
    itr.rescue = j["rescue"].asInt(); // 救出数
    i++;
  }
  
  return list;
}

void SaveScoreList(vector<score_t>&& scoreList) {
  // スコア順にソート
  sort(scoreList.begin(), scoreList.end(),
    [] (const score_t& l, const score_t& r) {
      return l.score > r.score;
    }
  );
  
  ofxJSON json;
  
  // json形式に変換
  int i = 1;
  for (auto&& s : scoreList) {
    string name = IntToStrDigit(i, 3);
    json["Score"][name]["score"]  = s.score;
    json["Score"][name]["rescue"] = s.rescue;
    ++i;
  }
  
  // jsonの書き出し
  json.save(g_scoreListSavePath);
  
  ofLog() << "Save Score to \"" + g_scoreListSavePath + "\"";
}
