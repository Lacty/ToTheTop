﻿
/**
 * @file   gameTitle.h
 * @brief  ゲームタイトルのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


//! @brief ゲームタイトルのシーンクラスです
class GameTitle : public ofxScene {
private:
	yCamera     cam_;
	BackGround  bg_;
	weak_ptr<Player>  wp_player_;
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  void gui() override;
	void exit() override;

	bool nextSceneTrriger();
};
