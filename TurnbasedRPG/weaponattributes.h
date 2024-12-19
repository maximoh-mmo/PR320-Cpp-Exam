#pragma once
#include <unordered_map>

struct WeaponAttributes
{
	std::string Name;
	int NumD6;
	int DamageMod;
	int CombatValueMod;
};

const std::unordered_map<std::string, WeaponAttributes> weaponConfigs = {
{
	{"Ion Cannon",{"Ion Cannon",2,2,0}},
	{"Pulse Torpedo", {"Pulse Torpedo",3,3 - 2}},
	{"Single Laser", {"Single Laser",1,1,2}}
	}
};