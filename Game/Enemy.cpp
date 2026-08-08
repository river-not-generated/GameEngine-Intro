#include "pch.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"
#include <iostream>

void Enemy::Update(float dt) {
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player) {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();

        m_transform.rotation = rotation * nu::math::RAD_TO_DEG;

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;

    float rotate = 0.0f;

    /*SetRotation(m_transform.rotation + rotate * dt);*/

    nu::Vector2 forward{ 1.0f, 0.0f };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD) * thrust;
    AddVelocity(velocity * dt);

    //SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "PlayerBullet") {
        other->Destroy();
        m_destroyed = true;

        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.texture = nu::Resources().Get<nu::Texture>("textures/particle.png", nu::Engine::Get().GetRenderer());
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
        nu::Engine::Get().GetAudio().PlaySound("kill");
        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);
        ((SpaceGame*)m_scene->GetGame())->IncreaseKillCount();
        ((SpaceGame*)m_scene->GetGame())->UpdateSpawnTime();
    }
}
