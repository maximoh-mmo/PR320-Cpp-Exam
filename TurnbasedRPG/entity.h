#pragma once

#include <map>
#include "component.h"

class Entity
{
public:
	Entity();
	~Entity();

	void Update();

	void AddComponent(Component* component);

	//Nice to have for developer convenience...
	template <class T>
	T* AddComponent()
	{
		T* component = new T();
		AddComponent(component);
		return component;
	}

	Component* GetComponent(ComponentID id) const;

	//Nice to have for developer convenience...
	template <class T>
	T* GetComponent() const
	{
		return static_cast<T*>(GetComponent(T::ID));
	}

	void SendMessage(int id);

private:
    Entity(Entity& other) = delete;
	Entity(Entity&& other) = delete;
	Entity& operator=(Entity& other) = delete;
	Entity& operator=(Entity&& other) = delete;

	//map is a sorted container, iteration will be in component id order
	std::map<ComponentID, Component*> _components;
};