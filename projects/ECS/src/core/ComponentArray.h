#pragma once

#include "Types.h"
#include <array>
#include <unordered_map>

//interface in which all component arrays will use so that component manager can destroy regardless of concrete implementation
class IComponentArray{
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray{
    public:
        //Add a component to a specific entity
        void InsertData(Entity entity, T component);
        //remove data from a specific entity
        void RemoveData(Entity entity);
        //get data about a specific entity
        T& GetData(Entity entity);
        //destroy component data about entity
        void EntityDestroyed(Entity entity) override;
    private:
        std::array<T, MAX_ENTITIES> m_componentArray;
        std::unordered_map<Entity, size_t> m_entityToIndexMap;
        std::unordered_map<size_t, Entity> m_indexToEntityMap;
        size_t m_size;
};

//function definitions
template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component){
    if(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end()){
        //doesn't exist so implement error handling
        return;
    }
    //put entry at the end of array
    size_t index = m_size;
    m_entityToIndexMap[entity] = index;
    m_indexToEntityMap[index] = entity;
    m_componentArray[index] = component;
    m_size++;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity){

}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity){

}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity){

}