
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

	shared_ptr<Player> player_;

	void moveCam();
	float offsetY_;
public:
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
	void gui() override;

	void keyPressed(int key) override;
};
