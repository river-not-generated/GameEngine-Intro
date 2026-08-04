#pragma once

#include "Actor.h"

struct BulletDesc : public nu::ActorDesc {
	float speed;
};

class Bullet : public nu::Actor {
public:
	Bullet() = default;
	Bullet(const BulletDesc& bulletDesc) : Actor{ bulletDesc }, m_speed{ bulletDesc.speed } {}

	void Update(float dt) override;

	float GetSpeed() { return m_speed; }

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
};