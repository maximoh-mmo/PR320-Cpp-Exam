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

void PlayerInputComponent::AssignStats(int startingPoints)
{
	auto availablePoints = startingPoints;
	auto copy = _stats;
	while (availablePoints > 0)
	{
		std::cout << "Strength is added to your weapon damage on a successful hit.\n";
		std::cout << "Dexterity is subtracted from incoming damage.\n";
		std::cout << "Constitution adds to your starting and maximum Hit Points.\n";
		std::cout << "Initiative determines your order in combat, Highest attacks first\n\n";
		std::cout << "You have " << availablePoints << " points remaining.\n";
		std::cout << "1. Strength - "<< copy["Strength"] << "\n";
		std::cout << "2. Dexterity - " << copy["Dexterity"] << "\n";
		std::cout << "3. Constitution - " << copy["Constitution"] << "\n";
		std::cout << "4. Initiative - " << copy["Initiative"] << "\n";
		std::cout << "5. Combat - " << copy["Combat"] << "\n";
		std::cout << "0. Reset stats.\n";
		std::cout << "Which stat would you like to increase?\n";		
		int stat = 0;
		while (true) {
			std::cin >> stat;
			if (std::cin.fail() || stat < 1 || stat > availablePoints) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please try again.\n";
			}
			else {
				break;
			}
		}
		std::string statName;
		switch (stat)
		{
		case 1:
			statName = "Strength";
			break;
		case 2:
			statName = "Dexterity";
			break;
		case 3:
			statName = "Constitution";
			break;
		case 4:
			statName = "Initiative";
			break;
		case 5:
			statName = "Combat";
			break;
		case 0:
			copy = _stats;
			availablePoints = startingPoints;
		}
		std::cout << "How many points would you like to add to " << statName << "?\n";
		int points = 0;
		while (true) {
			std::cin >> points;
			if (std::cin.fail() || points < 0 || points > availablePoints) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please try again.\n";
			}
			else {
				break;
			}
		}
		system("cls");
		copy[statName] += points;
		availablePoints -= points;
	}
	_stats = copy;
}

void PlayerInputComponent::CalculateHP()
{
	_stats["MaxHitpoints"] += _stats["Constitution"]*4;
	_stats["Hitpoints"] = _stats["MaxHitpoints"];
}

void PlayerInputComponent::Init()
{
	InputComponent::Init();
    _stats = {
        {"Strength" , 0},
        {"Dexterity" , 0},
        {"Constitution" , 0},
        {"MaxHitpoints" , 20},
        {"Hitpoints" , 20},
        {"Initiative" , 0},
        {"Strength" , 0}
    };
	int availablePoints = 30;
	std::cout << "Welcome Captain! Are you ready to take charge of your Star Fighter?.\n";
	std::cout << "You are the last hope for the galaxy. You must defeat the enemy ships to save the galaxy.\n";
	std::cout << "How would you like to distribute your starting stats?\n";
	std::cout << "You have 30 points to distribute between Strength, Dexterity, Constitution, Initiative and Combat.\n\n";
	
	AssignStats(availablePoints);
	CalculateHP();
	GetOwner().SendMessage(2);
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
