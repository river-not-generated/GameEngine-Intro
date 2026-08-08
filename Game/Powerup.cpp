#include "pch.h"
#include "Powerup.h"
#include "Engine.h"

void Powerup::Update(float dt) {
    nu::Particle particle;
    particle.position = { m_transform.position };
    particle.texture = nu::Resources().Get<nu::Texture>("textures/particle.png", nu::Engine::Get().GetRenderer());
    particle.lifespan = 0.5f;
    particle.velocity = { nu::RandomFloat(-100.0f, 100.0f), nu::RandomFloat(-100.0f, 100.0f) };
    Actor::Update(dt);
}