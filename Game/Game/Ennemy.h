#ifndef ENNEMY_H
#define ENNEMY_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"
#include "../Libs/Collision.h"

#define HURTED_TIME 0.5f
#define SPEED 200.0f
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

typedef struct Collision
{
	sfSprite* idle;
	sfSprite* walk;
}Collision;

typedef struct Ennemy
{
	EnnemyAnim anim;
	EnnemyState state;
	sfBool isHurted;
	sfBool isFlipped;
	float hurtedTime;
	Collision collision;
	sfVector2f position; 
	float speed;        
	int direction;    
} Ennemy;


void LoadEnnemy(void);
void OnMousePressedEnnemy(sfMouseButtonEvent _mouse, sfRenderWindow* _render);
void UpdateEnnemy(float _dt, sfRenderWindow* _render);
void DrawEnnemy(sfRenderWindow* _render);
#endif