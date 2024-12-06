#include "Game.h"
#include "Player.h"
#include "Ennemy.h"

Game game = { 0 };

void LoadBackground();
void DrawBackground(sfRenderWindow* _render);

#pragma region CoreGame
void LoadGame(void)
{
	LoadBackground();
	LoadPlayer();
	LoadEnnemy();
}

void UpdateGame(float _dt, sfRenderWindow* _render)
{
	UpdatePlayer(_dt, _render);
	UpdateEnnemy(_dt);
}

void OnKeyPressedGame(sfKeyEvent _key, sfRenderWindow* _render)
{
	OnKeyPressedPlayer(_key);
	switch (_key.code)
	{
	default:
		break;
	}
}

void OnMousePressedGame(sfMouseButtonEvent _mouse, sfRenderWindow* _render)
{
	OnMousePressedEnnemy(_mouse, _render);
}

void DrawGame(sfRenderWindow* _render)
{
	DrawBackground(_render);
	DrawEnnemy(_render);
	DrawPlayer(_render);
}

#pragma endregion

void LoadBackground()
{
	game.background.texture = sfTexture_createFromFile("Assets/Sprites/Background.png", NULL);
	game.background.sprite = sfSprite_create();

	sfSprite_setTexture(game.background.sprite, game.background.texture, sfTrue);
}

void DrawBackground(sfRenderWindow* _render)
{
	sfRenderWindow_drawSprite(_render, game.background.sprite, NULL);
}