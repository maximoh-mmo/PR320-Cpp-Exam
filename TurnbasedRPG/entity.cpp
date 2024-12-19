#include "entity.h"

Entity::Entity()
{
    
}

Entity::~Entity()
{
	for (auto& it : _components)
		delete it.second;
}

void Entity::Update()
{
	for (auto& it : _components)
	{
		if(it.second->IsEnabled())
			it.second->Update();
	}
}

void Entity::AddComponent(Component* component)
{
	if (_components.find(component->GetID()) != _components.end())
		throw std::exception("Component already exists");

	_components.insert(std::make_pair(component->GetID(), component));
	component->SetOwner(*this);
	component->Init();
}

Component* Entity::GetComponent(ComponentID id) const
{
	auto it = _components.find(id);
	if (it != _components.end())
		return it->second;
	return nullptr;
}

void Entity::SendMessage(int id)
{
	for (auto& kvp : _components)
		kvp.second->OnMessage(id);
}