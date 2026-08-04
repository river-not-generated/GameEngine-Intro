#pragma once

#include "Actor.h"

struct PowerupDesc : public nu::ActorDesc {

};

class Powerup : public nu::Actor {
public:
	Powerup() = default;
	Powerup(const PowerupDesc& powerupDesc) : Actor{ powerupDesc } {}

	void Update(float dt) override;

private:
};