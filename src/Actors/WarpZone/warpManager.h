
/**
* @file   warpManager.h
* @brief  ワープゾーンマネージャ−
*
* @author f.naoto
* @date   2017.1.8
*/
#pragma once


//! @brief ワープゾーンマネージャークラス
class WarpManager : public Actor {
private:
	weak_ptr<WarpZone> wp_warpZone_;
	weak_ptr<Actor> wp_player_;
	weak_ptr<BrickManager> wp_brickMgr_;
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