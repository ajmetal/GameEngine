#pragma once

//#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <iostream>

#include "Component.h"

class Entity
{
private:
    std::unordered_map<const std::type_info*, Component*> m_components;
    bool m_isActive;

public:
    Entity();
    Entity(Entity&);
    Entity(Entity&&);
    void operator=(Entity&);
    void operator=(Entity&&);
    Entity(const char* name);
    virtual ~Entity();

    const char* m_name;

    void ListComponents();

    template<typename T, typename ...TArgs>
    T* AddComponent(TArgs && ...args)
    {
        T* component = new T(this, std::forward<TArgs>(args)...);
        m_components[&typeid(*component)] = component;
        return component;
    }

    template <typename T>
    T* GetComponent() {
        return static_cast<T*>(m_components[&typeid(T)]);
    }

    template <typename T>
    bool HasComponent() {
        return (m_components.find(&typeid(T)) != m_components.end());
    }

    void Update(const float& deltaTime);
    void Render();
    void Destroy();
    bool Initialize();
    bool Start();

    bool SetActive(bool isActive);
   
    bool IsActive() const;
 

};

