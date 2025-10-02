#include "EntityManager.h"

EntityManager::EntityManager(){
    //initialize queue, array, and living entity count
    //populate the queue with available entities
    m_availableEntities = std::queue<Entity>();
    for(Entity entity = 0; entity < MAX_ENTITIES; entity++){
        m_availableEntities.push(entity);
    }

    //make sure all signatures are cleared
    for(Signature& signature: m_signatures){
        signature.reset();
    }

    //set to 0 because there are no currently living entities
    m_livingEntityCount = 0;
}

Entity EntityManager::CreateEntity(){
    //implement error handling if no available entities to be created
    if(!(m_livingEntityCount < MAX_ENTITIES)){
        //exit the program for now until a better solution is created
        exit(1);
    }

    //get available id from the queue and return it
    Entity id = m_availableEntities.front();
    m_availableEntities.pop();

    //id is now a living entity, make sure that we account for it's creation
    m_livingEntityCount++;

    return id;
}

void EntityManager::DestroyEntity(Entity entity){
    //error handling if entity is out of range
    if(!(entity < MAX_ENTITIES)){
        //exit program for now until better error handling is created
        exit(1);
    }

    //reset the entities signature
    m_signatures[entity].reset();
    //push it back onto the queue so the id can be reused
    m_availableEntities.push(entity);
    //make sure to account for the fact that the id isn't living anymore
    m_livingEntityCount--;
}

void EntityManager::SetSignature(Entity entity, Signature signature){
    //error handling if entity is out of range
    if(!(entity < MAX_ENTITIES)){
        //exit program for now until better error handling is created
        exit(1);
    }

    //set the signature
    m_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity){
    //error handling if entity is out of range
    if(!(entity < MAX_ENTITIES)){
        //exit program for now until better error handling is created
        exit(1);
    }

    //return the signature for the entity
    return m_signatures[entity];
}