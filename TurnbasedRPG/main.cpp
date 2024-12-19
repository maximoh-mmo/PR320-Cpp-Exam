#include <iostream>
#include "combatsystem.h"
#include "entity.h"
#include "gamestatecomponent.h"

class GameStateComponent;

int main()
{
    Entity gameController;
    GameStateComponent* gameState = gameController.AddComponent<GameStateComponent>();
    Entity combatSystemEntity;
    CombatSystem* combatSystem = combatSystemEntity.AddComponent<CombatSystem>();
    while (gameState->IsRunning())
    {
        while (!combatSystem->IsGameOver())
        {
            combatSystem->Update();
        }
    }
    std::cout << "\n I'm sorry captain, on this occasion we were overpowered. Better luck next time.";
    return 0;
}
