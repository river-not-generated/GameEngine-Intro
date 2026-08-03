#pragma once

#include "Actor.h"

struct PowerupDesc : public nu::ActorDesc {

};

class Powerup : public nu::Actor {
public:
	Powerup() = default;
	Powerup(const PowerupDesc& powerupDesc) : Actor{ powerupDesc } {}

	Powerup(const nu::Transform& transform) : Actor{ transform } {
	}
	Powerup(const nu::Transform& transform, const nu::Model& model)
		: Actor{ transform, model } {
	}

	void Update(float dt) override;

private:
};