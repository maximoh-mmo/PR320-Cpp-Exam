#pragma once
#include <memory>
#include "component.h"

class CombatSystem;
class Entity;

class EnemyFactory
{
public:
	EnemyFactory(CombatSystem* combat_system);
	~EnemyFactory() = default;

	std::unique_ptr<Entity> CreateEnemy(bool isBoss);

private:
	CombatSystem* _combat_system;
};