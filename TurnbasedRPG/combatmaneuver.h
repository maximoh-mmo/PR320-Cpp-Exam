#pragma once
#include <array>

enum class CombatManeuver
{
	StandardAttack,
	SweepingStrike,
	PowerStrike,
	Count
};

// String list of names for combat maneuvers
constexpr std::array<const char*, static_cast<int>(CombatManeuver::Count)> combatManeuverNames = {
	"StandardAttack",
	"SweepingStrike",
	"PowerStrike"
};

constexpr const char* CombatManeuverStringName(CombatManeuver combat_maneuver) { 
	return combatManeuverNames[static_cast<int>(combat_maneuver)]; }

// Static assertion to ensure enum and string list are synchronized
static_assert(static_cast<int>(CombatManeuver::Count) == combatManeuverNames.size(),
	"Mismatch between CombatManeuver enum and string list size!");

// Operator override to allow for iteration using enum count to define max size
inline bool operator<(int lhs, CombatManeuver rhs) {
	return lhs < static_cast<int>(rhs);
}