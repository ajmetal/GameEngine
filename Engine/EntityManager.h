#pragma once

#include <iostream>

#include <vector>
#include <queue>
#include "Entity.h";

class EntityManager
{
public:
    void Update(const float& deltaTime);
    void Render();
    void ClearData();
    bool HasNoEntities();
    void ListAllEntities();
    void ListAllComponents();
    Entity* AddEntity(const char* name);
    Entity* SetEntityActive(const char* name, bool active = true);
    // need to establish a "prefab" system for this first?
    //std::queue<Entity*> AddPool(const std::type_info*, unsigned int count);
    std::vector<Entity*> GetEntities() const;
    unsigned int GetEntityCount();
    void Initialize();
    void Start();
    EntityManager();
    ~EntityManager();
private:
    bool m_initializing = false;
    std::vector<Entity*> m_entities;
    std::unordered_map<const std::type_info*, std::queue<Entity*>> m_pools;
};

