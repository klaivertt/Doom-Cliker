#ifndef GAME_H
#define GAME_H

#include "../Libs/Common.h"

typedef struct Game
{
	Images background;
	float score;
}Game;

void LoadGame(void);
void UpdateGame(float, sfRenderWindow* _render);
void OnKeyPressedGame(sfKeyEvent, sfRenderWindow* _render);
void OnMousePressedGame(sfMouseButtonEvent, sfRenderWindow* _render);
void DrawGame(sfRenderWindow* _render);
#endif