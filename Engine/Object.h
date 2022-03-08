#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ECS.h"
#include <type_traits>
#include "Vector3.h"

//components:
#include "Transform.h"
#include "Image.h"
#include "Animation.h"
#include "Collider.h"
#include "Text.h"
#include "Controller.h"
#include "Sound.h"

class Object
{	
public:
	virtual ~Object();
	//BeginPlay function

	virtual void Construct();

	//start function
	virtual void Start();

	//update function
	virtual void Update();

	//fixUpdate function
	virtual void FixUpdate();

	//Set my Transform parent to a Transform
	void SetParent(Transform* parentTransform);

	//Tells the level to remove this object
	void Destroy(Object* obj);

	//Set the tag of this object
	void SetTag(std::string newTag);

	//Get this tag
	std::string GetTag();

	//if is running during the game
	bool isActive = true;
	//if is holding to be destroyed
	bool pendingDestroy = false;


	//Check if can cast to T Class
	template<typename T>
	bool CheckCastTo()
	{
		T* child = dynamic_cast<T*>(this);
		if (child != nullptr)
		{
			return true;
		}
		return false;
	}

	//Casts to T Class
	template<typename T>
	T* CastTo()
	{
		T* child = dynamic_cast<T*>(this);
		if (child != nullptr)
		{
			return child;
		}
		throw std::invalid_argument("Can not cast to T Class");
		return nullptr;
	}

	//Adds a component to the entity
	template<typename T, typename... TArgs>
	T* AddComponent(TArgs&&... args)
	{
		T* comp(new T(std::forward<TArgs>(args)...));

		Component* uptr(comp);

		if (comp->Init())
		{
			compList[getComponentTypeID<T>()] = comp;
			compBitset[getComponentTypeID<T>()] = true;
			comp->myObject = this;
			components.emplace_back(std::move(uptr));
			return comp;
		}
		return static_cast<T*>(nullptr);
	}

	//Get component in the entity
	template<typename T>
	inline T& GetComponent() const {
		auto ptr(compList[getComponentTypeID<T>()]);

		return *static_cast<T*>(ptr);
	}

	//Get components in the entity
	template<typename T>
	inline std::vector<T*> GetComponents() const {
		auto ptr(compList[getComponentTypeID<T>()]);

		std::vector <T*> compResult;
		for (int i = 0; i < components.size(); ++i)
		{
			if (dynamic_cast<T*>(components[i]) != nullptr)
			{
				compResult.push_back(static_cast<T*>(components[i]));
			}
		}

		return compResult;
	}

	//has component in entity
	template<typename T>
	inline bool HasComponent() const {
		return compBitset[getComponentTypeID<T>()];
	}

protected:
	//my parent
	Transform* parent = nullptr;
	//Calls the destructors of this components

	void DestroyComponents();

	//Tag of the object
	std::string myTag = "";


	//list with all components
	ComponentList compList{};
	//list if component exist
	ComponentBitset compBitset{};
	//vector with my components
	std::vector<Component*> components{};
};

