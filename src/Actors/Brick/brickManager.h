
/**
 * @file   brickManager.h
 *
 * @author y.akira
 * @date   2016.12.29
 */

#pragma once


class BrickSpawner;

class BrickManager : public Actor {
private:
  vector<list<weak_ptr<Actor>>> bricks_;

  int                 column_;             // 画面分割数
  int                 verticalLimit_;      // 最高高低差
  float               deltaTime_;          // 起動してからの経過時間
  float               spawnInterval_;      // Brickを生成する時間区間
  
  ofVec2f             brickSize_;          // Brickのサイズ
  
  float               spawnTime_;          // スポナーからBrickが生成されるまでの時間
  float               fallTime_;           // 落下時間
  AnimCurve           curve_;              // 落下アニメーションのイージング
  
  
  // 仲間生成のパラメータ
  float               cspDeltaTime_;
  float               cspInterval_;

  //int                 safetyCol(int c);    // 与えられたColumnの数値を正しい数値に変換する

public:
  BrickManager();
  ~BrickManager() {}

	void                setup() override;
	void                update(float deltaTime) override;
	void                draw() override;
  void                gui() override;
  
  //                  指定した位置にBrickを生成する
  void                createBrick(int col, float posY);
  void                createNextBrick(int col);
  
  //                  指定した位置にBrickを生成(スポナー使用
  void                spawnBrick(int col, float posY, const ofVec2f& startOffset, float spwTime, float fallTime, AnimCurve curve);
  void                spawnNextBrcik(int col, const ofVec2f& startOffset, float spwTime, float fallTime, AnimCurve curve);
  
  //                  仲間の生成 落下なし(めんどいからじゃないんだからね！
  void                createCsp(int col);
  
  float               getInterval() const;
  float               getSpawnTime() const;
  float               getFallTime() const;
  float               getCspInterval() const;
  
  void                setInterval(float interval);
  void                setSpawnTime(float time);
  void                setFallTime(float time);
  void                setCspInterval(float interval);
};
