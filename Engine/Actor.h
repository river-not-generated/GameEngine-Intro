#pragma once

#include "Transform.h"
#include "Model.h"
#include "Resource.h"
#include "Object.h"
#include "Framework/Component.h"

#include <string>
#include <memory>
#include <vector>

namespace nu {
    class Scene;
    class Texture;

    struct ActorDesc : public ObjectDesc {
        std::string tag;
        Transform transform;
        Vector2 velocity{ 0.0f, 0.0f };
        float damping = 0.0f;
        res_t<Model> model;
        res_t<Texture> sprite;
        float lifespan = 0.0f;
    };

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) : 
            Object{ actorDesc }
            , m_tag{actorDesc.tag}
            , m_transform{ actorDesc.transform }
            , m_velocity{ actorDesc.velocity }
            , m_damping{ actorDesc.damping }
            , m_lifespan{ actorDesc.lifespan } {
        }

        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

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

        void SetTag(const std::string& tag) { m_tag = tag; }

        void SetTransform(const Transform& transform) {
            m_transform = transform;
        }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }


        bool GetDestroyed() const { return m_destroyed; }
        void Destroy(bool destroyed = true) { m_destroyed = destroyed; }

        Scene* GetScene() const { return m_scene; };

        float GetRadius(float error = 0.5f) const;

        virtual void Read(const json::value_t& value) override;

        void AddComponent(std::unique_ptr<Component> component);

        template <std::derived_from<Component> T>
        T* GetComponent();

        friend Scene;

    protected:
        std::string m_tag;
        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
        float m_damping = 0.0f;
        float m_lifespan = 0.0f;
        bool m_destroyed = false;

        std::vector<std::unique_ptr<Component>> m_components;

        Scene* m_scene = nullptr;
    };

    template <std::derived_from<Component> T>
    inline T* Actor::GetComponent() {
        for (auto& component : m_components) {
            auto result = dynamic_cast<T*>(component.get());
            if (result) return result;
        }
        return nullptr;
    }
}