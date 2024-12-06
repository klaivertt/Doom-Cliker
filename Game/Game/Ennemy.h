#ifndef ENNEMY_H
#define ENNEMY_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"
#include "../Libs/Collision.h"

#define HURTED_TIME 0.5f
#define SPEED 200.0f
#define MIN_IDLE_TIME 1.0f
#define ATTACK_TIME_LENGTH 1.0f
#define ATTACK_ANIM_TIME 0.5f
#define MAX_HEALTH 100.0f
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
	sfTexture* idle;
	sfTexture* walk;
	sfTexture* attack;
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
	float moveTime;
	float minIdleTime;
	float attackTime;
	float attackAnimTime;
	sfBool isAttacking;
	float health;
	sfText* heathText;
} Ennemy;


void LoadEnnemy(void);
void OnMousePressedEnnemy(sfMouseButtonEvent _mouse, sfRenderWindow* _render);
void UpdateEnnemy(float _dt);
void DrawEnnemy(sfRenderWindow* _render);
#endif