
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
  
  score_t(const score_t& src)
  : score ( src.score  )
  , rescue( src.rescue ) {}
};


