#pragma once
#include <memory>
#include <vector>

#include "combatmaneuver.h"
#include "combatsystem.h"
#include "component.h"

class InputComponent : public Component
{
public:
    InputComponent();
    virtual ~InputComponent();
	virtual ComponentID GetID() const override { return ComponentID::Input;}
    void SetCombatSystem(const CombatSystem* combatSystem) { _combatSystem = combatSystem; }
    virtual Entity* GetTarget() const = 0;
    virtual CombatManeuver GetAttack() const = 0;
    static const ComponentID ID = ComponentID::Input;
protected:
    const CombatSystem* _combatSystem;
};

class PlayerInputComponent : public InputComponent
{
public:
    virtual ~PlayerInputComponent();
    virtual void Init() override;
    virtual Entity* GetTarget() const override; //query entities from m_CombatSystem
    virtual CombatManeuver GetAttack() const override;
};

class AIInputComponent : public InputComponent
{
public:
    virtual ~AIInputComponent();
    virtual Entity* GetTarget() const override { return _combatSystem->GetPlayer(); } //query entities from m_CombatSystem
    virtual CombatManeuver GetAttack() const override;
};

