
/**
* @file   brickManager.h
* @brief  ï¿½ï¿½ï¿½ï¿½ï¿½Kï¿½}ï¿½lï¿½[ï¿½Wï¿½ï¿½ï¿½[
*
* @author ninja
* @date   2016.12.27
*/

#pragma once
//‰æ–Ê‚ğ‚Ç‚Ì‚®‚ç‚¢‚ÅŠ„‚é‚©
#define ROW 10
#define COLUMN 5

/**
 * @brief ƒŒƒ“ƒK‚Ì¶¬‚Æ—‰ºˆÊ’u‚ğw’è‚·‚éƒNƒ‰ƒX
 */
class BrickManager : public Actor {
private:
	list<shared_ptr<Brick>> bricks_;
	float count_;
	void sponeBrick(ofVec2f& pos);

	ofVec2f windowSize_;

	//—‰º’n“_‚ğŠi”[
	ofVec2f fallPoints_[COLUMN][ROW];
	//ƒŒƒ“ƒK‚ª‚ ‚é‚©‚Ç‚¤‚©
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