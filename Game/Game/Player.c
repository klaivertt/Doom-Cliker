#include "Player.h"

Player player = { 0 };

void LoadPlayer(void)
{
	CreateSprite(&player.mouse, (sfVector2f){0,0}, "Assets/Sprites/Cursor.png");
	SetSpriteOrigin(&player.mouse, (sfVector2f) { 2, 2 });
	CreateSprite(&player.gun, (sfVector2f){SCREEN_W/2, SCREEN_H}, "Assets/Sprites/Shotgun.png");
	SetSpriteOrigin(&player.gun, (sfVector2f) { 2, 1 });
}


void UpdatePlayer(float _dt, sfRenderWindow* _render)
{
	sfVector2i mouse = sfMouse_getPositionRenderWindow(_render);

	sfSprite_setPosition(player.mouse, (sfVector2f) { mouse.x, mouse.y });
}

void DrawPlayer(sfRenderWindow* _render)
{
	sfRenderWindow_drawSprite(_render, player.mouse, NULL);
	sfRenderWindow_drawSprite(_render, player.gun, NULL);
}

void OnKeyPressedPlayer(sfKeyEvent _key)
{
	switch (_key.code)
	{
	default:
		break;
	}
}
