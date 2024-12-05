#ifndef MENU_H
#define MENU_H

#include "../Libs/Common.h"
#include "../Libs/Animations.h"

#define MAX_BUTTONS 5

typedef struct Button
{
	Images image;
	sfRectangleShape* rectangle;
	sfText* text;
}Button;

typedef struct Menu
{
	sfFont* font;
	Images background;
	Animation playerIdle;
	Animation* currentAnim;
	Button buttons[MAX_BUTTONS];
	int currentButton;
}Menu;

void LoadMenu(void);
void OnKeyPressedMenu(sfKeyEvent _key, sfRenderWindow* const _render);
void UpdateMenu(float);
void DrawMenu(sfRenderWindow*);
void CleanMenu(void);

#endif