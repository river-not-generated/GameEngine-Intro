#include "pch.h"
#include "Bullet.h"
#include "Engine.h"
#include "Player.h"
#include "Core/Factory.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt) {
    nu::Vector2 forward{ 1.0f, 0.0f };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD) * m_speed;
    SetVelocity(velocity);

    Actor::Update(dt);
}

void Bullet::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}