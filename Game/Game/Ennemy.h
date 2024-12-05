#ifndef ENNEMY_H
#define ENNEMY_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"
#include "../Libs/Collision.h"

#define HURTED_TIME 0.5f

typedef enum EnnemyState
{
	IDLE,
	WALK,
	HURT,
	ATTACK
}EnnemyState;

typedef struct EnnemyAnim
{
	Animation idle;
	Animation walk;
	Animation hurt;
	Animation attack;
	Animation* current;
}EnnemyAnim;

typedef struct Ennemy
{
	EnnemyAnim anim;
	EnnemyState state;
	sfBool isHurted;
	float hurtedTime;
	sfSprite* collisionTexture;
}Ennemy;

void LoadEnnemy(void);
void OnMousePressedEnnemy(sfMouseButtonEvent _mouse, sfRenderWindow* _render);
void UpdateEnnemy(float _dt, sfRenderWindow* _render);
void DrawEnnemy(sfRenderWindow* _render);
#endif