#ifndef PLAYER_H
#define PLAYER_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"
#include "../Libs/Collision.h"
#include "../Libs/Utilities.h"

typedef struct PlayerAnim
{
	Animation* current;
}PlayerAnim;

typedef struct Player
{
	sfSprite* mouse;
	sfSprite* gun;
}Player;

void LoadPlayer(void);
void UpdatePlayer(float _dt, sfRenderWindow* _render);
void DrawPlayer(sfRenderWindow*);
void OnKeyPressedPlayer(sfKeyEvent);
#endif

