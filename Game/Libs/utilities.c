#include "Utilities.h"

void LoadUtilities(void)
{
	//utilities.font = sfFont_createFromFile("Assets/Fonts/font.ttf");
}

void CreateSprite(sfSprite** const _sprite, sfVector2f position, const char* _filepath)
{
	*_sprite = sfSprite_create();
	sfSprite_setPosition(*_sprite, position);

	sfTexture* texture = sfTexture_createFromFile(_filepath, NULL);
	sfSprite_setTexture(*_sprite, texture, sfTrue);
}

void SetSpriteOrigine(sfSprite** _sprite, sfVector2f divide)
{
	sfVector2u size = sfTexture_getSize(sfSprite_getTexture(*_sprite));
	sfSprite_setOrigin(*_sprite, (sfVector2f) { size.x / divide.x, size.y / divide.y});
}

void CreateText()
{

}