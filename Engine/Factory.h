#pragma once
#include <memory>
#include <map>
#include <iostream>

#include "Object.h"
#include "Singleton.h"
#include "StringUtils.h"

namespace nu
{
    class ICreator
    {
    public:
        virtual ~ICreator() = default;
        virtual std::unique_ptr<Object> Create() = 0;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class Creator : public ICreator
    {
    public:
        std::unique_ptr<Object> Create() override { return make_unique<T>(); }
    };

    class Factory : public Singleton<Factory> {
    public:
        template <typename T>
            requires std::derived_from<T, Object>
        void Register(const std::string& name);

        template <typename T = class Object>
            requires std::derived_from<T, Object>
        std::unique_ptr<T> Create(const std::string& name);

    private:
        std::map<std::string, std::unique_ptr<ICreator>> m_registry;
    };

    // --- DEFINITIONS ---
    template<typename T>
        requires std::derived_from<T, Object>
    inline void Factory::Register(const std::string& name)
    {
        std::string lowerName = ToLower(name);
        if (m_registry.contains(lowerName)) {
            std::cerr << "Object [" << lowerName << "] already registered" << std::endl;
            return;
        }
        m_registry[lowerName] = std::make_unique<Creator<T>>();
    }

    template<typename T>
        requires std::derived_from<T, Object>
    inline std::unique_ptr<T> Factory::Create(const std::string& name)
    {
        std::string lowerName = ToLower(name);
        if (!m_registry.contains(lowerName)) {
            std::cerr << "Object [" << lowerName << "] not registered, cannot create" << std::endl;
            return std::unique_ptr<T>();
        }

        auto iter = m_registry.find(lowerName);
        // create unique ptr to object
        auto object = iter->second->Create();

        // check if object is derived from T
        T* derived = dynamic_cast<T*>(object.get());
        if (derived) {
            // release unique ptr ownership
            object.release();

            // create new unique ptr with derived ptr
            return std::unique_ptr<T>(derived);
        }
        else {
            std::cerr << "Object [" << lowerName << "] not derived from specified type" << std::endl;
        }

        return std::unique_ptr<T>();
    }
}