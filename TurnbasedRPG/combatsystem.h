#pragma once

#include <vector>
#include <memory>
#include "combatmaneuver.h"
#include "component.h"
#include "enemyfactory.h"

struct Attack
{
    std::vector<Entity*> targets;
    CombatManeuver maneuver;
};

class CombatSystem : public Component
{
public:
    CombatSystem();
    virtual ~CombatSystem() override;
    virtual ComponentID GetID() const override { return ComponentID::CombatSystem; }
    virtual void Init() override;
    virtual void Update() override;
    Entity* GetPlayer() const { return _player; }
    bool IsGameOver() const { return _bIsGameOver; }
    const std::vector<std::unique_ptr<Entity>>& GetEntities() const { return _entities; }

private:
    Entity* _player;
    EnemyFactory* _enemyfactory;
    std::vector<std::unique_ptr<Entity>> _entities;
    int _round;
    bool _bIsGameOver;

    void RoundStart();
    void SortEntitiesByInitiative();
    void CleanupEntities();
    Attack SelectTargets(const Entity* entity) const;
    void ResolveCombat(const Entity* attacker, Entity* target, int maneuver_attack_modifier, int maneuver_damage_multiplier);
    void ExecuteManeuver(Entity* attacker, const Attack& attack_detail);
    void ProcessCombat(Entity* entity);
};