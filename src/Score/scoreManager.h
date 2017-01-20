
/**
 * @file   scoreManager.h
 *
 * @author y.akira
 * @date   2017.01.15
 */

#pragma once


struct score_t {
  int score;
  int rescue;
  
  score_t()
  : score ( 0 )
  , rescue( 0 ) {}
  
  score_t(int s, int r)
  : score ( s )
  , rescue( r ) {}
  
  score_t(const score_t& src)
  : score ( src.score  )
  , rescue( src.rescue ) {}
};


//! 保存されたスコアを取得する
vector<score_t> GetScoreList();

//! スコアを保存する
void SaveScoreList(vector<score_t>&& scoreList);
