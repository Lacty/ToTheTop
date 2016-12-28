
/**
* @file   brickManager.h
* @brief  レンガマネージャー
*
* @author ninja
* @date   2016.12.27
*/

#pragma once
//画面をどのぐらいで割るか
#define ROW 10
#define COLUMN 5

/**
 * @brief レンガの生成と落下位置を指定するクラス
 */
class BrickManager : public Actor {
private:
	list<shared_ptr<Brick>> bricks_;
	float count_;
	void sponeBrick(ofVec2f& pos);

	ofVec2f windowSize_;

	//落下地点を格納
	ofVec2f fallPoints_[COLUMN][ROW];
	//レンガがあるかどうか
	bool existances_[COLUMN][ROW];

	int row_;
	int column_;
	int numX_;
	int numY_;

	int minFallPoint_[2];
	int fallTerms_;
	int terms_;

	void setMinPoint();
	float getSplitWindowX(int c);
	float getSplitWindowY(int r);
public:
	void setup() override;
	void update(float deltaTime) override;
	void draw() override;
};