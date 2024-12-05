#ifndef PLAYER_H
#define PLAYER_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"
#include "../Libs/Collision.h"

typedef struct PlayerAnim
{
	Animation fall;
	Animation land;
	Animation idle;
	Animation* current;
}PlayerAnim;

typedef struct Player
{
	PlayerAnim anim;
	int index;
	sfVector2f velocity;
	float speed;
	int targetX;
	sfBool moving;
	sfBool left;
}Player;

void LoadPlayer(void);
void UpdatePlayer(float);
void DrawPlayer(sfRenderWindow*);
void OnKeyPressedPlayer(sfKeyEvent);

#endif

