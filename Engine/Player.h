#pragma once

#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc {
	float speed;
};

class Player : public nu::Actor {

	public:
		Player() = default;
		Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } {}

		Player(float speed, const nu::Transform& transform) : Actor{ transform } {
			m_speed = speed; 
		}
		Player(float speed, const nu::Transform& transform, const nu::Model& model) 
			: Actor{ transform, model } {
			m_speed = speed;
		}

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

		void ActivateTriple() { m_tripleShot = true; m_powerupTime = 10.0f;}
		void DeactivateTriple() { m_tripleShot = false; }

		float GetSpeed() { return m_speed; }
	
	private:
		int m_ammo = 0;
		float m_speed = 400.0f;
		float m_powerupTime = 0.0f;
		float m_dashCooldown = 0.0f;

		bool m_tripleShot = true;
};