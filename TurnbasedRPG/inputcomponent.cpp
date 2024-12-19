#include <iostream>
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "Util.h"

InputComponent::InputComponent()
    : _combatSystem(nullptr)
{
    
}

InputComponent::~InputComponent()
{
    
}

PlayerInputComponent::~PlayerInputComponent()
{
    
}

void PlayerInputComponent::Init()
{
	InputComponent::Init();
}

Entity* PlayerInputComponent::GetTarget() const
{
    std::cout << "The following " << _combatSystem->GetEntities().size() - 1 << " Enemies attack:\n" << "Your current HP is :" << GetOwner().GetComponent<FighterComponent>()->Get_Stat("Hitpoints") << "\n";
    int j = 1;
    std::map<int, int> indexes;
    for (int i = 0; i < _combatSystem->GetEntities().size(); ++i) {

        if (_combatSystem->GetEntities()[i].get() == &GetOwner())
        {
            continue;
        }

        auto* fighter = _combatSystem->GetEntities()[i]->GetComponent<FighterComponent>();
        if (fighter)
        {
            std::cout << j << ". " << fighter->Get_Name() << " - Current HP = " << fighter->Get_Stat("Hitpoints")<<"\n";
            indexes.insert(std::make_pair(j, i));
            ++j;
        }
    }
    std::cout << "Which do you choose to attack?";
    int enemyindex = 0;
    while (true) {
        std::cin >> enemyindex;
        if (std::cin.fail() || enemyindex < 1 || enemyindex > j-1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
        }
        else {
            break;
        }
    }
    std::cout << "Selected enemy is : " << _combatSystem->GetEntities()[indexes.find(enemyindex)->second]->GetComponent<FighterComponent>()->Get_Name() << "\n";
    return _combatSystem->GetEntities()[indexes.find(enemyindex)->second].get();
}

CombatManeuver PlayerInputComponent::GetAttack() const
{
    std::cout << "Pick your attack:\n";
    for (int i = 0; i < CombatManeuver::Count ; ++i)
    {
        std::cout <<i+1 << ". " << combatManeuverNames[i] << "\n";
    }
    int attack_index = 0;
    while (true) {
        std::cin >> attack_index;
        if (std::cin.fail() || attack_index < 1 || attack_index > static_cast<int>(CombatManeuver::Count)+1){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
        }
        else {
            break;
        }
    }
    return static_cast<CombatManeuver>(attack_index - 1);
}

AIInputComponent::~AIInputComponent()
{
    
}

CombatManeuver AIInputComponent::GetAttack() const
{
    return Util::Rand(9) < 9 ? CombatManeuver::StandardAttack : CombatManeuver::PowerStrike;
}
