#pragma once

//Order in the enum dictates update and messaging order!
enum class ComponentID
{
	Input,
	Fighter,
	CombatSystem
};

class Entity;

class Component
{
public:
	Component()
		: _owner(nullptr)
		, _enabled(true)
	{}
	virtual ~Component() {}

	virtual ComponentID GetID() const = 0;
	virtual void Update() {};
	virtual void Init() {};
	virtual void OnMessage(int id) {};
	Entity& GetOwner() const { return *_owner; }
	void SetEnabled(bool enable) { _enabled = enable; }
	bool IsEnabled() const { return _enabled; }

private:
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&& other) = delete;

	friend class Entity;
	void SetOwner(Entity& entity) { _owner = &entity; }

	Entity* _owner;
	bool _enabled;
};