#include "Menu.h"
#include "../Libs/Collision.h"
#include "../GameState.h"

Menu menu = { 0 };

void LoadMenuBackground(void);
void DrawMenuBackground(sfRenderWindow*);

void LoadMenuButton(void);
void ButtonChangeState(sfRenderWindow* const _render);
void UpdateMenuButton(float);
void DrawMenuButton(sfRenderWindow*);

#pragma region GameLoop

void LoadMenu(void)
{
	LoadMenuBackground();
}


void OnKeyPressedMenu(sfKeyEvent _key, sfRenderWindow* const _render)
{
	switch (_key.code)
	{
	case sfKeyZ:
		menu.currentButton--;
		if (menu.currentButton < 0)
		{
			menu.currentButton = MAX_BUTTONS - 1;
		}
		break;
	case sfKeyS:
		menu.currentButton++;
		if (menu.currentButton > MAX_BUTTONS - 1)
		{
			menu.currentButton = 0;
		}
		break;
	case sfKeyUp:
		menu.currentButton--;
		if (menu.currentButton < 0)
		{
			menu.currentButton = MAX_BUTTONS - 1;
		}
		break;
	case sfKeyDown:
		menu.currentButton++;
		if (menu.currentButton > MAX_BUTTONS - 1)
		{
			menu.currentButton = 0;
		}
		break;
	case sfKeySpace:
		ButtonChangeState(_render);
		break;
	case sfKeyEnter:
		ButtonChangeState(_render);
		break;
	default:
		break;
	}
}

void UpdateMenu(float _dt)
{
	UpdateMenuButton(_dt);
}

void DrawMenu(sfRenderWindow* _render)
{
	DrawMenuBackground(_render);
	DrawMenuButton(_render);
}

void CleanMenu(void)
{
}

#pragma endregion

#pragma region Background
void LoadMenuBackground(void)
{

}

void DrawMenuBackground(sfRenderWindow* _render)
{

}

#pragma endregion

#pragma region Buttons

void LoadMenuButton(void)
{
	menu.currentButton = 0;
}

void ButtonChangeState(sfRenderWindow* const _render)
{
	switch (menu.currentButton)
	{
	case 0:
		SetGameState(GAME);
		break;
	case 2:
		//SetGameState(GAME);
		break;
	case 4:
		sfRenderWindow_close(_render);
		break;
	default:
		break;
	}
}

void UpdateMenuButton(float _dt)
{
}

void DrawMenuButton(sfRenderWindow* _render)
{

}

#pragma endregion