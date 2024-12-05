#ifndef GAMESTATE_H
#define GAMESTATE_H

typedef enum GameState
{
	MENU,
	GAME
}GameState;

void SetGameState(GameState);
GameState GetGameState(void);

#endif

