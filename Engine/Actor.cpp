#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Engine.h"
#include "Texture.h"

namespace nu
{
    void Actor::Update(float dt) {
        // lifespan
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0);
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= (1.0f / ((1.0f) + m_damping * dt));

        m_transform.position.x = nu::math::Wrap(0.0f, Engine::Get().GetRenderer().GetWindowWidth(), m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(0.0f, Engine::Get().GetRenderer().GetWindowHeight(), m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const {
        if (m_model) {
            renderer.DrawModel(*m_model, m_transform);
        }
        if (m_sprite) {
            renderer.DrawTexture(*m_sprite, m_transform);
        }
    }

    //
    float Actor::GetRadius(float error) const {
        if (m_model) 
            return m_model->GetRadius() * m_transform.scale * (1.0f - error);
        if (m_sprite)
            return m_sprite->GetSize().Length() * 0.5f * (1.0f - error);
         
        return 0.0f;
    }
}