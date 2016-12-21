
/**
 * @file   sandbox.h
 * @brief  サンドボックスシーン
 *         各自で作った機能を試すためのシーンです
 *
 * @author y.akira
 * @date   2016.12.14
 */

#pragma once


//! @brief サンドボックスのシーンクラスです
class Sandbox : public ofxScene {
private:
	float count_;
public:
  void setup() override;
  void update(float deltaTime) override;
  void draw() override;
  
};
