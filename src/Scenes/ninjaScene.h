
/**
 * @file   ninjaScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#pragma once


//! @brief テスト用シーンクラス
class NinjaScene : public ofxScene {
private:
	yCamera     cam_;
	BackGround  bg_;
	weak_ptr<Player>  wp_player_;
	weak_ptr<BrickManager> wp_brickMgr_;
	ofTrueTypeFont font_;
	bool spawn_;

	void stageSpawn();
	bool nextSceneTrriger();
public:
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void gui() override;
	void exit() override;

	void keyPressed(int key) override;
};
