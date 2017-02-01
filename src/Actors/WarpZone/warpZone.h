
#pragma once


class WarpZone : public Actor {
private:
	bool warp_;
	float degree_;
	ofImage tex_;
	ofVec2f destPos_;
	Player* player_;
	ofxAnimatableFloat x_, y_;
	weak_ptr<BrickManager> wp_brickMgr_;
	ofVec2f holeScale_;
	vector<ofVec2f> holePos_;
	int holeValue_;

	void drawHole(ofVec2f& pos);
public:
	WarpZone();
	virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* c_actor) override;

	void setDistination(const ofVec2f& pos);
};