
#pragma once


class WarpZone : public Actor {
private:
	int w_, h_;
	bool warp_;
	float degree_;
	ofVec2f destPos_;
	Player* player_;
	ofxAnimatableFloat x_, y_;
	vector<ofColor> holeColors_;
	vector<ofVec2f> holeScales_;

	//
	void drawWarpHole(const ofColor& color,const ofVec2f& pos,const ofVec2f& size);

	//輪を制御する変数・関数
	ofVec2f holeScale_;
	vector<ofVec2f> holePos_;
	int holeValue_;
	void drawHole(const ofColor& color,const ofVec2f& pos);
public:
	WarpZone();
	virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* c_actor) override;

	void setDistination(const ofVec2f& pos);
	bool getWarp();
};