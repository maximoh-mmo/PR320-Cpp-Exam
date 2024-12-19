#pragma once
#include "Component.h"

class GameStateComponent : public Component
{
public:
	enum class State {
        MainMenu,
        InGame,
        GameOver
    };
    // Game State starts in MainMenu.
    GameStateComponent()
		: _currentState(State::MainMenu), _currentLevel(1), _bIsRunning(true), _bExitRequested(false)
	{
	}

    ComponentID GetID() const override { return ComponentID::GameState; }

    // Getters and Setters
    State GetCurrentState() const { return _currentState; }
    void SetCurrentState(State state) { _currentState = state; }

    int GetCurrentLevel() const { return _currentLevel; }
    void SetCurrentLevel(int level) { _currentLevel = level; }

    bool IsRunning() const { return _bIsRunning; }
    void SetRunning(bool running) { _bIsRunning = running; }

	bool Quit() const { return _bExitRequested; }
private:
    State _currentState;
    int _currentLevel;
    bool _bIsRunning;
    bool _bExitRequested;
};