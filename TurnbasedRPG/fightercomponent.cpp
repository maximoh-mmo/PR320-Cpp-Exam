#include "fightercomponent.h"
#include <iostream>
#include <algorithm>

FighterComponent::~FighterComponent()
{    
}

void FighterComponent::Init()
{
	Component::Init();

	// default stats to be overwritten depending on conditional factors
	// Enemy/Boss/Player etc.
	_stats = {
		{"Strength" , 0},
		{"Dexterity" , 0},
		{"Constitution" , 0},
		{"MaxHitpoints" , 20},
		{"Hitpoints" , 20},
		{"Initiative" , 0},
		{"Strength" , 0}
	};
}

int FighterComponent::Get_Stat(std::string stat)
{
    auto it = _stats.find(stat);
    return it != _stats.end() ? it->second : INT_MIN;
}

void FighterComponent::Set_Stat(std::string stat, int value)
{
    auto it = _stats.find(stat);
    if (it == _stats.end())
    {
        throw std::runtime_error("Stat does not exist");
    }
    it->second = value;
}

void FighterComponent::Set_Stats(std::map<std::string, int> stats)
{
    _stats = stats;
}

void FighterComponent::Equip_Weapon(WeaponAttributes weapon)
{
    _weapon_attributes = weapon;
}

void FighterComponent::OnMessage(int id)
{
	Component::OnMessage(id);
	if (id == 9)
	{
		// set enabled false pending delete	
		SetEnabled(false);
	}
}
