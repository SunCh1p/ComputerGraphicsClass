#pragma once

#include "Types.h"
#include <queue>
#include <array>

class EntityManager{
    public:
        //Constructor
        EntityManager();

        //returns entity upon creation
        Entity CreateEntity();

        //Removes entity and reinserst its value back into the creation queu
        void DestroyEntity(Entity entity);

        //Sets the signature for an entity
        void SetSignature(Entity entity, Signature signature);

        //Gets the signature for an entity
        Signature GetSignature(Entity entity);
    private:
        //used to dispatch an entity id should an entity be created
        std::queue<Entity> m_availableEntities;

        //array to track signatures of all entities
        std::array<Signature, MAX_ENTITIES> m_signatures;

        //track how many entities are currently dispatched
        uint32_t m_livingEntityCount;

};