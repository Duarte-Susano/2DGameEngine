#pragma once

#include <iostream>
#include <bitset>
#include <array>

//Components
class Component;

//Size of id
using ComponentTypeID = std::size_t;

//Get component ID
ComponentTypeID getUniqueComponentID();

//get component of tipe
template<typename T>
ComponentTypeID getComponentTypeID() noexcept;

//max number of components per entity
constexpr std::size_t MAX_COMPONENTS = 32;

//arrray of is component in entity
using ComponentBitset = std::bitset<MAX_COMPONENTS>;
//array of components
using ComponentList = std::array<Component*, MAX_COMPONENTS>;

//Returns the ID of specific component
template<typename T>
ComponentTypeID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "Type not base on component!");
	static const ComponentTypeID typeID = getUniqueComponentID();
	return typeID;
}

