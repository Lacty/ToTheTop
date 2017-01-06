
#pragma once


class WarpZone : public Actor {
private:
	bool warp_;
	Actor* c_Pactor_;
	ofVec2f destination_;

	ofxAnimatableFloat x_, y_;

	float count_;
public:
	virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* c_actor) override;

	void setDistination(ofVec2f& pos);
};