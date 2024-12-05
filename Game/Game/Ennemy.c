#include "../Game/Ennemy.h"
#include "../Libs/Utilities.h"
#include "../Libs/Collision.h"

Ennemy ennemy = { 0 };

void EnnemySetState(EnnemyState const _state);
void UpdateEnnemyAnimation();
void CollideMouseEnnemy(sfRenderWindow* _render);

void LoadEnnemy(void)
{
	ennemy.collisionTexture = sfTexture_createFromFile("Assets/Sprites/WalkDamages.png",NULL);
	EnnemySetState(WALK);
	CreateAnimation(&ennemy.anim.idle, "Assets/Sprites/Idle.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.walk, "Assets/Sprites/Walk.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.hurt, "Assets/Sprites/Hurt.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.attack, "Assets/Sprites/Attack.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	ennemy.anim.current = &ennemy.anim.idle;
	sfSprite_setPosition(ennemy.anim.current->sprite, (sfVector2f) { SCREEN_W / 2, SCREEN_H / 2 });

	SetSpriteOrigine(&ennemy.anim.idle.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.walk.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.hurt.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.attack.sprite, (sfVector2f) { 2, 1 });

	ennemy.isHurted = sfFalse;
	ennemy.hurtedTime = HURTED_TIME;
}

void OnMousePressedEnnemy(sfMouseButtonEvent _mouse, sfRenderWindow* _render)
{
	switch (_mouse.button)
	{
	case sfMouseLeft:
		CollideMouseEnnemy(_render);
		break;
	default:
		break;
	}
}


void UpdateEnnemy(float _dt, sfRenderWindow* _render)
{
	UpdateEnnemyAnimation();
	sfSprite_setPosition(ennemy.anim.current->sprite, (sfVector2f) { SCREEN_W / 2, SCREEN_H / 2 });
}

void DrawEnnemy(sfRenderWindow* _render)
{
	sfRenderWindow_drawSprite(_render, ennemy.anim.current->sprite, NULL);
}

void EnnemySetState(EnnemyState const _state)
{
	ennemy.state = _state;
}

void UpdateEnnemyAnimation()
{
	switch (ennemy.state)
	{
	case IDLE:
		ennemy.anim.current = &ennemy.anim.idle;
		break;
	case WALK:
		ennemy.anim.current = &ennemy.anim.walk;
		break;
	case HURT:
		ennemy.anim.current = &ennemy.anim.hurt;
		break;
	case ATTACK:
		ennemy.anim.current = &ennemy.anim.attack;
		break;
	default:
		break;
	}
}

void CollideMouseEnnemy(sfRenderWindow* _render)
{
	sfFloatRect enemyHitbox = sfSprite_getGlobalBounds(ennemy.anim.current->sprite);

	sfVector2i mouse = sfMouse_getPositionRenderWindow(_render);

	if (CollisionPointRect(enemyHitbox, mouse))
	{
		sfTexture* enemyTexture = sfSprite_getTexture(ennemy.collisionTexture);
		sfImage* enemyImage = sfTexture_copyToImage(ennemy.collisionTexture);
		sfVector2u pixelPos = { mouse.x - enemyHitbox.left, mouse.y - enemyHitbox.top };
		sfColor pixelColor = sfImage_getPixel(enemyImage, pixelPos.x, pixelPos.y);

		// Click sur un pixel opaque
		if (pixelColor.a == 255)
		{
			printf("HIT\n");
		}

		sfImage_destroy(enemyImage);

	}
}
