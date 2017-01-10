
/**
 * @file   leveler.h
 *
 * @author y.akira
 * @date   2017.01.04
 */

#pragma once


/**
 * @brief 難易度を調整するクラス
 */
class Leveler : public Actor {
private:
  int   level_;          ///< 現在の難易度
  int   defaultLevel_;   ///< 初期レベル
  int   levelInterval_;  ///< 難易度を上げる区間(スコアを参照
  
  // レベルアップ毎にどれだけパラメータを変更させるかのパラメータ
  float lu_Interval_;
  float lu_FallTime_;
  float lu_SpawnTime_;

  weak_ptr<BrickManager> brickMgr_;
  weak_ptr<uiMeter>      meter_;

  // 難易度を上げる
  void levelUp(int up);

public:
  Leveler();
  ~Leveler() {}

  void setup() override;
  void update(float deltaTime) override;
  void gui() override;
  
};
