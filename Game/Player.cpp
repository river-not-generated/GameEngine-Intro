#include "pch.h"
#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>

void Player::Update(float dt) {

    // movement control for the player square (WASD or arrows)
    // nu::Vector2 force{ 0.0f, 0.0f };

    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W) || nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
        thrust = m_speed;
        nu::Particle particle;
        particle.position = m_transform.position;
        particle.texture = nu::Resources().Get<nu::Texture>("textures/particle.png", nu::Engine::Get().GetRenderer());
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = { nu::RandomFloat(-100.0f, 100.0f), nu::RandomFloat(-200.0f, 200.0f) };

        nu::Engine::Get().GetPS().AddParticle(particle);
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S) || nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) {
        thrust = -m_speed;
    }

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A) || nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) {
        rotate = -180.0f;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D) || nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) {
        rotate = 180.0f;
    }

    // dash
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LSHIFT) && m_dashCooldown == 0.0f) {
        thrust = m_speed * 125;
        for (int i = 0; i < 50; i++) {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.texture = nu::Resources().Get<nu::Texture>("textures/particle.png", nu::Engine::Get().GetRenderer());
            particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
            particle.velocity = { nu::RandomFloat(-100.0f, 100.0f), nu::RandomFloat(-200.0f, 200.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
        m_dashCooldown = 2.5f;
        nu::Engine::Get().GetAudio().PlaySound("thrust");
    }

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1.0f, 0.0f };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD) * thrust;
    AddVelocity(velocity * dt);


    //SetVelocity(GetVelocity() + (force * dt));

    // fire bullet
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        for (int i = 0; i < (m_tripleShot ? 3 : 1); i++) {
            nu::Transform trans = {m_transform.position, m_transform.rotation, 1.0f};
            switch (i) {
                case 1: 
                    trans.rotation += 5.0f;
                    break;
                case 2: 
                    trans.rotation -= 5.0f;
                    break;
            }
            BulletDesc desc;
            desc.name = "Bullet";
            desc.tag = "PlayerBullet";
            // desc.model = assets::bulletModel;
            desc.sprite = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
            desc.transform = trans;
            desc.speed = 2000.0f;
            desc.damping = 0.5f;
            desc.lifespan = 1.0f;

            std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(desc);
            m_scene->AddActor(std::move(bullet));
        }
        nu::Engine::Get().GetAudio().PlaySound("fire");
    }
    m_powerupTime = std::max(0.0f, m_powerupTime - dt);
    m_dashCooldown = std::max(0.0f, m_dashCooldown - dt);
    if (m_tripleShot && m_powerupTime <= 0.0f) DeactivateTriple();

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "Enemy") {
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

        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }

    if (other->GetTag() == "TripleShot") {
        ActivateTriple();
        other->Destroy();
        nu::Engine::Get().GetAudio().PlaySound("powerup");
    }
    if (other->GetTag() == "Heart") {
        ((SpaceGame*)m_scene->GetGame())->AddHeart();
        other->Destroy();
        nu::Engine::Get().GetAudio().PlaySound("powerup");
    }
}