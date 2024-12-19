#include <algorithm>
#include <iostream>
#include "entity.h"
#include "combatsystem.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "enemyfactory.h"
#include "Util.h"

CombatSystem::CombatSystem()
	: _player(nullptr)
	, _enemyfactory(nullptr)
	, _round(0)
	, _bIsGameOver(false)
{
}

CombatSystem::~CombatSystem()
{
    delete _enemyfactory;
}

void CombatSystem::Init()
{
    _enemyfactory = new EnemyFactory(this);
    std::unique_ptr<Entity> player = std::make_unique<Entity>();
    _player = player.get();
    player->AddComponent<FighterComponent>();
    player->GetComponent<FighterComponent>()->Set_Name("You");
    InputComponent* input = player->AddComponent<PlayerInputComponent>();
    input->SetCombatSystem(this);
    _entities.push_back(std::move(player));
    RoundStart();
};

void CombatSystem::RoundStart()
{
    //Create enemies
    ++_round;
    if (_round % 3 == 0)
    {
        std::cout << "Boss Round";
        _entities.push_back(_enemyfactory->CreateEnemy(true));
    }
    else 
    {
        int numEnemies = Util::Rand(2, 4);
        for (int i = 0; i < numEnemies; ++i)
        {
            _entities.push_back(_enemyfactory->CreateEnemy(false));
        }
    }
}

void CombatSystem::Update()
{
    // Sort by initiative
    SortEntitiesByInitiative();
    
    // Iterate through Sorted Entities
    for (int i = 0; i < _entities.size(); ++i)
    {
        ProcessCombat(_entities[i].get());
    }

    CleanupEntities();
}

void CombatSystem::SortEntitiesByInitiative()
{
    std::sort(_entities.begin(), _entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) {
        int initiativeA = a->GetComponent<FighterComponent>()->Get_Stat("Initiative");
        int initiativeB = b->GetComponent<FighterComponent>()->Get_Stat("Initiative");
        // Check for draw and return random
        if (initiativeA == initiativeB) {
            return Util::Rand(1) == 0;
        }
        // Higher initiative comes first
        return initiativeA > initiativeB;
        });
}

void CombatSystem::ProcessCombat(Entity* entity)
{
    auto combat_stats = SelectTargets(entity);

    if (combat_stats.targets.empty()) return;

    ExecuteManeuver(entity, combat_stats);
}

Attack CombatSystem::SelectTargets(const Entity* entity) const
{
    std::vector<Entity*> targets;
    // Query the input component for the primary target
    Entity* target = entity->GetComponent<InputComponent>()->GetTarget();
    if (target)
    {
        targets.push_back(target);
    }
    CombatManeuver maneuver = entity->GetComponent<InputComponent>()->GetAttack();
    if (maneuver != CombatManeuver::SweepingStrike)
    {
        return Attack{ targets,maneuver };
    }
    // If an ae attack is selected we need to add all enemies for attack.
    targets.clear();
    for (const auto& otherEntity : _entities)
    {
        if (otherEntity && otherEntity.get() != entity)
        {
            targets.push_back(otherEntity.get());
        }
    }
    return Attack{ targets,maneuver };
}

void CombatSystem::ExecuteManeuver(Entity* attacker, const Attack& attack_detail)
{
    int manuever_attack_modifier = 0;
    int maneuver_damage_multiplier = 1;

    switch (attack_detail.maneuver)
    {
    case CombatManeuver::SweepingStrike:
        manuever_attack_modifier -= 4;
        break;

    case CombatManeuver::PowerStrike:
        manuever_attack_modifier -= 8;
        maneuver_damage_multiplier = 2;
        break;

    case CombatManeuver::StandardAttack:
        // No changes for StandardAttack
        break;

    default:
        throw std::runtime_error("Unknown maneuver type");
    }

    for (auto target : attack_detail.targets)
    {
        ResolveCombat(attacker, target, manuever_attack_modifier, maneuver_damage_multiplier);
    }
}

void CombatSystem::ResolveCombat(const Entity* attacker, Entity* target, int maneuver_attack_modifier, int maneuver_damage_multiplier)
{
    WeaponAttributes attack_weapon = attacker->GetComponent<FighterComponent>()->Get_Weapon();
    // If attacker's Combat stat - maneuver is less than 0 default to 0
    int attack_modifier = std::max((maneuver_attack_modifier + attacker->GetComponent<FighterComponent>()->Get_Stat("Combat")), 0);
    // After adding combat base + maneuver modifier, add in weapon modifier and dice roll
    int attack = Util::Rand(20) + attack_modifier + attack_weapon.CombatValueMod;

    WeaponAttributes defense_weapon = target->GetComponent<FighterComponent>()->Get_Weapon();
    int defense = Util::Rand(20) + target->GetComponent<FighterComponent>()->Get_Stat("Combat") + defense_weapon.CombatValueMod;


    if (attack > defense)
    {
        int damage = attacker->GetComponent<FighterComponent>()->Get_Stat("Strength") + attack_weapon.DamageMod;

        // Roll dice for weapon damage
        for (int i = 1; i < attack_weapon.NumD6; ++i)
        {
            damage += Util::Rand(6);
        }

        // Mitigate damage
        damage = std::max(0, damage - target->GetComponent<FighterComponent>()->Get_Stat("Dexterity"));

        // Apply damage
        int newHp = target->GetComponent<FighterComponent>()->Get_Stat("Hitpoints") - damage;
        target->GetComponent<FighterComponent>()->Set_Stat("Hitpoints", newHp);

        std::cout << attacker->GetComponent<FighterComponent>()->Get_Name() << " successfully attacked "
            << target->GetComponent<FighterComponent>()->Get_Name() << " causing "
            << damage << "points of damage.\n";
        // change message for 1 point of damage.
        if (newHp <= 0)
        {
            if (target != _player) {
                std::cout << target->GetComponent<FighterComponent>()->Get_Name() << " was destroyed!!\n";
            }
            target->SendMessage(9); // Entity is "killed"
        }
    }
    else
    {
        std::cout << attacker->GetComponent<FighterComponent>()->Get_Name() << " attempted to attack "
            << target->GetComponent<FighterComponent>()->Get_Name() << ".\nBut they were outmaneuvered.\n";
    }
}

void CombatSystem::CleanupEntities()
{
    // Iterate and remove entities with inactive fighter components
    for (auto it = _entities.begin(); it != _entities.end();)
    {
        if ((*it)->GetComponent<FighterComponent>()->IsEnabled() != true) {
            if (it->get() == _player)
            {
                // Player is flagged for deletion the game should end.
                _bIsGameOver = true;
            }
            // As we remove the entity there is no need to advance the iterator.
            it = _entities.erase(it);
        }
        else
        {
            // Advance the iterator
            ++it;
        }
    }
}