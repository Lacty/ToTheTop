
/**
* @file   brickManager.h
* @brief  �����K�}�l�[�W���[
*
* @author ninja
* @date   2016.12.27
*/

#pragma once
//��ʂ��ǂ̂��炢�Ŋ��邩
#define ROW 10
#define COLUMN 5

/**
 * @brief �����K�̐����Ɨ����ʒu���w�肷��N���X
 */
class BrickManager : public Actor {
private:
	list<shared_ptr<Brick>> bricks_;
	float count_;
	void sponeBrick(ofVec2f& pos);

	ofVec2f windowSize_;

	//�����n�_���i�[
	ofVec2f fallPoints_[COLUMN][ROW];
	//�����K�����邩�ǂ���
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