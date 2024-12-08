#include "../Game/Ennemy.h"
#include "../Libs/Utilities.h"
#include "../Libs/Collision.h"
#include "../Libs/Text.h"

Ennemy ennemy = { 0 };

void EnnemySetState(EnnemyState const _state);
void UpdateEnnemyAnimation();
void HeathUpdate();
void CollideMouseEnnemy(sfRenderWindow* _render);
void RespawnEnnemy(void);

void LoadEnnemy(void)
{
	ennemy.collision.idle = sfTexture_createFromFile("Assets/Sprites/IdleDamages.png", NULL);
	ennemy.collision.walk = sfTexture_createFromFile("Assets/Sprites/WalkDamages.png", NULL);
	ennemy.collision.attack = sfTexture_createFromFile("Assets/Sprites/AttackDamages.png", NULL);

	EnnemySetState(WALK);
	CreateAnimation(&ennemy.anim.idle, "Assets/Sprites/Idle.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.walk, "Assets/Sprites/Walk.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.hurt, "Assets/Sprites/Hurt.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.attack, "Assets/Sprites/Attack.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	CreateAnimation(&ennemy.anim.dead, "Assets/Sprites/Dead.png", 1, 1, 1, sfTrue, (sfVector2f) { 0, 0 });
	ennemy.anim.current = &ennemy.anim.idle;
	ennemy.position = (sfVector2f){ SCREEN_W / 2, SCREEN_H / 1.5f };
	ennemy.speed = SPEED;
	ennemy.direction = -1;

	SetSpriteOrigine(&ennemy.anim.idle.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.walk.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.hurt.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.attack.sprite, (sfVector2f) { 2, 1 });
	SetSpriteOrigine(&ennemy.anim.dead.sprite, (sfVector2f) { 2, 1 });

	ennemy.isHurted = sfFalse;
	ennemy.isFlipped = sfFalse;
	ennemy.hurtedTime = HURTED_TIME;

	ennemy.moveTime = rand() % 5;
	ennemy.minIdleTime = MIN_IDLE_TIME;
	ennemy.attackTime = (rand() % 4) + 2;
	ennemy.attackAnimTime = ATTACK_ANIM_TIME;

	ennemy.health = MAX_HEALTH;
	ennemy.isAttacking = sfFalse;
	ennemy.isAlive = sfTrue;
	ennemy.respawnTimer = 3.0f;
	InitText(&ennemy.heathText, "Health", 25, (sfVector2f) { 0, 0 });
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

void UpdateEnnemy(float _dt)
{
	sfFloatRect enemyBox = sfSprite_getLocalBounds(ennemy.anim.current->sprite);

	ennemy.attackTime -= _dt;
	if (ennemy.attackTime < 0)
	{
		EnnemySetState(ATTACK);
		ennemy.isHurted = sfFalse;
		ennemy.isAttacking = sfTrue;
	}
	if (ennemy.state == WALK)
	{
		ennemy.moveTime -= _dt;
		if (ennemy.moveTime < 0)
		{
			EnnemySetState(IDLE);
		}
		else
		{
			ennemy.position.x += ennemy.direction * ennemy.speed * _dt;
		}

		if (ennemy.position.x < enemyBox.width / 2)
		{
			ennemy.position.x = enemyBox.width / 2;
			ennemy.direction = 1;
		}
		else if (ennemy.position.x > SCREEN_W - enemyBox.width / 2)
		{
			ennemy.position.x = SCREEN_W - enemyBox.width / 2;
			ennemy.direction = -1;
		}

		if (ennemy.direction == -1)
		{
			ennemy.isFlipped = sfFalse;
		}
		else
		{
			ennemy.isFlipped = sfTrue;
		}
	}
	else if (ennemy.state == IDLE)
	{
		ennemy.minIdleTime -= _dt;
		if (ennemy.minIdleTime < 0)
		{
			int random = rand() % 100;
			if (random > 95)
			{
				ennemy.direction = (rand() % 2) ? 1 : -1;
				ennemy.moveTime = (rand() % 5) + 1;
				EnnemySetState(WALK);
				ennemy.minIdleTime = MIN_IDLE_TIME;
			}
		}
	}
	else if (ennemy.state == ATTACK)
	{
		ennemy.attackAnimTime -= _dt;
		if (ennemy.attackAnimTime < 0)
		{
			ennemy.attackAnimTime = ATTACK_ANIM_TIME;
			ennemy.isAttacking = sfFalse;
			EnnemySetState(WALK);
			ennemy.attackTime = (rand() % 6) + 2;
		}
	}
	if (ennemy.health <= 0)
	{
		ennemy.isAlive = sfFalse;
		EnnemySetState(DEAD);
	}
	else
	{
		ennemy.hurtedTime -= _dt;
		if (ennemy.hurtedTime < 0)
		{
			EnnemySetState(IDLE);
			ennemy.isHurted = sfFalse;
		}
	}

	if (!ennemy.isAlive)
	{
		ennemy.respawnTimer -= _dt;

		if (ennemy.respawnTimer <= 0)
		{
			RespawnEnnemy();
			ennemy.respawnTimer = 3.0f;
		}
	}

	sfSprite_setPosition(ennemy.anim.current->sprite, ennemy.position);
	UpdateEnnemyAnimation();
	UpdateText(&ennemy.heathText, "Health : %d", ennemy.health);
	sfFloatRect textBounds = sfText_getLocalBounds(ennemy.heathText);
	sfText_setOrigin(ennemy.heathText, (sfVector2f) { textBounds.width / 2, textBounds.height });
	sfText_setPosition(ennemy.heathText, (sfVector2f) { ennemy.position.x, ennemy.position.y - enemyBox.height - 25 });
}



void DrawEnnemy(sfRenderWindow* _render)
{
	sfRenderWindow_drawSprite(_render, ennemy.anim.current->sprite, NULL);
	sfRenderWindow_drawText(_render, ennemy.heathText, NULL);
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
		sfSprite_setPosition(ennemy.anim.idle.sprite, ennemy.position);
		ennemy.anim.current = &ennemy.anim.idle;
		break;
	case WALK:
		ennemy.anim.current = &ennemy.anim.walk;
		break;
	case HURT:
		sfSprite_setPosition(ennemy.anim.hurt.sprite, ennemy.position);
		ennemy.anim.current = &ennemy.anim.hurt;
		break;
	case ATTACK:
		sfSprite_setPosition(ennemy.anim.attack.sprite, ennemy.position);
		ennemy.anim.current = &ennemy.anim.attack;
		break;
	case DEAD:
		sfSprite_setPosition(ennemy.anim.dead.sprite, ennemy.position);
		ennemy.anim.current = &ennemy.anim.dead;
		break;
	default:
		break;
	}

	if (ennemy.isFlipped)
	{
		sfSprite_setScale(ennemy.anim.current->sprite, (sfVector2f) { -1, 1 });
	}
	else
	{
		sfSprite_setScale(ennemy.anim.current->sprite, (sfVector2f) { 1, 1 });
	}
}

void HeathUpdate()
{
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
		case ATTACK:
			enemyImage = sfTexture_copyToImage(ennemy.collision.attack);
			break;
		default:
			break;
		}

		sfVector2u pixelPos = { 0,0 };

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
		if (!ennemy.isHurted && !ennemy.isAttacking)
		{
			if (pixelColor.a == 255)
			{
				if (pixelColor.r == 255 && pixelColor.g == 255)
				{
					printf("CHEST HIT\n");
					ennemy.health -= 7;
				}
				else if (pixelColor.b == 255)
				{
					printf("ARMS HIT\n");
					ennemy.health -= 5;
				}
				else if (pixelColor.g == 255)
				{
					printf("LEGS HIT\n");
					ennemy.health -= 3;
				}
				else if (pixelColor.r == 255)
				{
					printf("HEAD SHOT\n");
					ennemy.health -= 10;
				}
				EnnemySetState(HURT);
				ennemy.isHurted = sfTrue;
				ennemy.hurtedTime = HURTED_TIME;
			}
		}

		sfImage_destroy(enemyImage);
	}
}

void RespawnEnnemy(void)
{
	// R�initialiser les attributs de l'ennemi
	ennemy.position = (sfVector2f){ SCREEN_W / 2, SCREEN_H / 1.5f };
	ennemy.speed = SPEED;
	ennemy.direction = (rand() % 2 == 0) ? -1 : 1;
	ennemy.isHurted = sfFalse;
	ennemy.isFlipped = sfFalse;
	ennemy.hurtedTime = HURTED_TIME;

	ennemy.moveTime = rand() % 5;
	ennemy.minIdleTime = MIN_IDLE_TIME;
	ennemy.attackTime = (rand() % 4) + 2;
	ennemy.attackAnimTime = ATTACK_ANIM_TIME;

	ennemy.health = MAX_HEALTH;
	ennemy.isAttacking = sfFalse;
	ennemy.state = IDLE;
	ennemy.anim.current = &ennemy.anim.idle;

	UpdateText(&ennemy.heathText, "Health : %d", ennemy.health);

	ennemy.isAlive = sfTrue;

	printf("Enemy respawned at position: (%f, %f)\n", ennemy.position.x, ennemy.position.y);
}
