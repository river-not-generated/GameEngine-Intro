#include "pch.h"
#include "Bullet.h"
#include "Engine.h"
#include "Player.h"

void Bullet::Update(float dt) {
    nu::Vector2 forward{ 1.0f, 0.0f };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD) * m_speed;
    SetVelocity(velocity);

    Actor::Update(dt);
}