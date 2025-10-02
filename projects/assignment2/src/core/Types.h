#pragma once

#include <bitset>
#include <cstdint>


//defining basic types for ecs
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

//define a Component id for component system, each component gets a unique id
using ComponentType = std::uint8_t;
//define what the max amount of components can be
const ComponentType MAX_COMPONENTS = 32;

//define what a signature is(a way to tell what entitys have what components)
using Signature = std::bitset<MAX_COMPONENTS>;

//define input buttons
enum class InputButtons{
    W,
    A,
    S,
    D
};