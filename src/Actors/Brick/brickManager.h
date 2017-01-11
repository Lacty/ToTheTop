
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
  vector<deque<weak_ptr<Actor>>> bricks_;

  int                 column_;             // 画面分割数
  int                 verticalLimit_;      // 最高高低差
  float               deltaTime_;          // 起動してからの経過時間
  float               spawnInterval_;      // Brickを生成する時間区間
  
  ofVec2f             brickSize_;          // Brickのサイズ
  
  float               spawnTime_;          // スポナーからBrickが生成されるまでの時間
  float               fallTime_;           // 落下時間
  AnimCurve           curve_;              // 落下アニメーションのイージング
  

public:
  BrickManager();
  ~BrickManager() {}

	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
  void gui() override;
  
  float getInterval() const;
  float getSpawnTime() const;
  float getFallTime() const;
  
  void  setInterval(float interval);
  void  setSpawnTime(float time);
  void  setFallTime(float time);
};
