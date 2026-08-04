#pragma once

#include "Transform.h"
#include "Model.h"

#include <string>
#include <memory>

namespace nu {
    class Scene;

    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity{ 0.0f, 0.0f };
        float damping = 0.0f;
        std::shared_ptr<Model> model;
        float lifespan = 0.0f;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) : m_name{actorDesc.name}, m_tag{actorDesc.tag}
            , m_transform{ actorDesc.transform }, m_velocity{ actorDesc.velocity }, m_damping{ actorDesc.damping }, 
            m_model { actorDesc.model }, m_lifespan{ actorDesc.lifespan } {
        }

        virtual void Update(float dt);

        // forward declaration only works on references and pointers
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const {
            return m_transform;
        }
        const Vector2& GetVelocity() const {
            return m_velocity;
        }

        void SetVelocity(const Vector2& velocity) {
            m_velocity = velocity;
        }
        void AddVelocity(const Vector2& velocity) {
            m_velocity += velocity;
        }
        void SetPosition(const Vector2& position) {
            m_transform.position = position;
        }
        void SetRotation(float rotation) {
            m_transform.rotation = rotation;
        }
        void SetScale(float scale) {
            m_transform.scale = scale;
        }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }


        bool GetDestroyed() const { return m_destroyed; }
        void Destroy(bool destroyed = true) { m_destroyed = destroyed; }

        Scene* GetScene() const { return m_scene; };

        float GetRadius(float error = 0.1f) const;
        void SetModel(std::shared_ptr<Model> model) { m_model = model; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;
        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
        float m_damping = 0.0f;
        float m_lifespan = 0.0f;
        bool m_destroyed = false;

        std::shared_ptr<Model> m_model;
        Scene* m_scene = nullptr;
    };
}