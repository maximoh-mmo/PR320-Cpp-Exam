#include "enemyfactory.h"
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "util.h"


EnemyFactory::EnemyFactory(CombatSystem* combat_system)
	:_combat_system(combat_system)
{
}

std::unique_ptr<Entity> EnemyFactory::CreateEnemy(bool isBoss)
{
	std::unique_ptr<Entity> enemy = std::make_unique<Entity>();
	enemy->AddComponent<FighterComponent>();
	enemy->GetComponent<FighterComponent>()->Set_Name(Util::RandomEnemyName(isBoss));
	InputComponent* input = enemy->AddComponent<AIInputComponent>();
	input->SetCombatSystem(_combat_system);
	return std::move(enemy);
}