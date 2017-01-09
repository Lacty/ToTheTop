
/**
* @file   warpManager.h
* @brief  ワープゾーンマネージャ－
*
* @author f.naoto
* @date   2017.1.8
*/
#pragma once


//! @brief ワープゾーンマネージャークラス
class WarpManager : public Actor {
private:
	shared_ptr<WarpZone> warpZone_;
	shared_ptr<Actor> player_;
	ofVec2f spawnPos_;
	ofVec2f destPos_;
	ofVec2f warpSize_;
	void spawnWarp();
public:
	WarpManager();
	void setup() override;
	void update(float deltaTime) override;
	void gui() override;
};