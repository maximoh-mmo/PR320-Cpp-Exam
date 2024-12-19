#include <iostream>
#include "combatsystem.h"
#include "entity.h"

int main()
{
    Entity combatSystemEntity;
    CombatSystem* combatSystem = combatSystemEntity.AddComponent<CombatSystem>();
    while (!combatSystem->IsGameOver())
    {
        combatSystem->Update();
    }
    std::cout << "\n I'm sorry captain, on this occasion we were overpowered. Better luck next time.";
    return 0;
}