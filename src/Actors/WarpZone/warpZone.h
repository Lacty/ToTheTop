
#pragma once


class WarpZone : public Actor {
private:
	bool warp_;
	Player* p_actor;
	float P_actorGravity;
	void warp(Player* actor, float deltaTime);
	ofVec2f destination;

public:
	virtual void setup() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* c_actor) override;

	void setDistination(ofVec2f& pos);
	void setDistination(float posX,float posY);
};