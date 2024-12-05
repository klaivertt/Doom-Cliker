#include "../Game/Ennemy.h"
#include "../Libs/Utilities.h"
#include "../Libs/Collision.h"

Ennemy ennemy = { 0 };

void EnnemySetState(EnnemyState const _state);
void UpdateEnnemyAnimation();
void CollideMouseEnnemy(sfRenderWindow* _render);

void LoadEnnemy(void)
{
	ennemy.collision.idle = sfTexture_createFromFile("Assets/Sprites/IdleDamages.png", NULL);
	ennemy.collision.walk = sfTexture_createFromFile("Assets/Sprites/WalkDamages.png", NULL);

	EnnemySetState(WALK);
	CreateAnimation(&ennemy.anim.idle, "Assets/Sprites/Idle.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.walk, "Assets/Sprites/Walk.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.hurt, "Assets/Sprites/Hurt.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.attack, "Assets/Sprites/Attack.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	ennemy.anim.current = &ennemy.anim.idle;
	ennemy.position = (sfVector2f){ SCREEN_W / 2, SCREEN_H / 1.5f };
	ennemy.speed = SPEED;
	ennemy.direction = -1;

	SetSpriteOrigine(&ennemy.anim.idle.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.walk.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.hurt.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.attack.sprite, (sfVector2f) { 2, 1 });

	ennemy.isHurted = sfFalse;
	ennemy.isFlipped = sfFalse;
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
	sfFloatRect enemyBox = sfSprite_getLocalBounds(ennemy.anim.current->sprite);
	ennemy.position.x += ennemy.direction * ennemy.speed * _dt;

	if (ennemy.position.x < 0 + enemyBox.width / 2 || ennemy.position.x > SCREEN_W - enemyBox.width / 2)
	{
		ennemy.direction *= -1;
		ennemy.isFlipped = (ennemy.direction < 0) ? sfTrue : sfFalse;

		sfSprite_setScale(ennemy.anim.current->sprite,(sfVector2f) {ennemy.isFlipped ? -1 : 1, 1});
	}

	sfSprite_setPosition(ennemy.anim.current->sprite, ennemy.position);
	UpdateEnnemyAnimation();
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

	if (ennemy.isFlipped)
	{
		sfSprite_setScale(ennemy.anim.current->sprite, (sfVector2f) { ennemy.isFlipped ? -1 : 1, 1 });
	}
	else
	{
		sfSprite_setScale(ennemy.anim.current->sprite, (sfVector2f) { -1, 1 });
	}
}


void CollideMouseEnnemy(sfRenderWindow* _render)
{
	sfFloatRect enemyHitbox = sfSprite_getGlobalBounds(ennemy.anim.current->sprite);

	sfVector2i mouse = sfMouse_getPositionRenderWindow(_render);

	if (CollisionPointRect(enemyHitbox, mouse))
	{
		sfImage* enemyImage = sfTexture_copyToImage(ennemy.collision.idle);

		switch (ennemy.state)
		{
		case IDLE:
			enemyImage = sfTexture_copyToImage(ennemy.collision.idle);
			break;
		case WALK:
			enemyImage = sfTexture_copyToImage(ennemy.collision.walk);
			break;
		default:
			break;
		}

		sfVector2u pixelPos;

		if (ennemy.isFlipped)
		{
			pixelPos.x = enemyHitbox.width - (mouse.x - enemyHitbox.left);
		}
		else
		{
			pixelPos.x = mouse.x - enemyHitbox.left;
		}

		pixelPos.y = mouse.y - enemyHitbox.top;
		sfColor pixelColor = sfImage_getPixel(enemyImage, pixelPos.x, pixelPos.y);

		// Click sur un pixel opaque
		if (pixelColor.a == 255)
		{
			printf("HIT\n");
		}

		sfImage_destroy(enemyImage);

	}
}
