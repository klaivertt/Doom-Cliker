#include "GameState.h"

GameState state;

void SetGameState(GameState _state)
{
    state = _state;
}

GameState GetGameState(void)
{
    return state;
}
