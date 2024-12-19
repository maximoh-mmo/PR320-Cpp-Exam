#pragma once
#include <map>
#include <string>
#include <vector>
#include "component.h"
#include "weaponattributes.h"

enum class CombatManeuver;

class FighterComponent : public Component
{
public:
    virtual ~FighterComponent() override;
	virtual ComponentID GetID() const override { return ComponentID::Fighter; }
	virtual void Init() override;
	virtual int Get_Stat(std::string stat);
	virtual std::string Get_Name() { return _name; }
	virtual void Set_Name(std::string value) { _name = value; }
	virtual void Set_Stat(std::string stat, int value);
	virtual void Set_Stats(std::map<std::string,int> stats);
	virtual void Equip_Weapon(WeaponAttributes weapon);
	virtual WeaponAttributes Get_Weapon() { return _weapon_attributes; }
    static const ComponentID ID = ComponentID::Fighter;
	void OnMessage(int id) override;
private:
	std::string _name;
	std::map<std::string, int> _stats;
	WeaponAttributes _weapon_attributes = { "Standard", 1, 1 , 1};
	std::vector<CombatManeuver> _combat_maneuvers;
};

