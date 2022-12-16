#pragma once

#include <iostream>

#include <vector>
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
    std::vector<Entity*> GetEntities() const;
    unsigned int GetEntityCount();
    void Initialize();
    void Start();
    EntityManager();
    ~EntityManager();
private:
    std::vector<Entity*> m_entities;
};

