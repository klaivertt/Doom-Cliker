#ifndef UTILITIES_H
#define UTILITIES_H

#include "Common.h"

void LoadUtilities(void);
void CreateSprite(sfSprite** const _sprite, sfVector2f position, const char* _filepath);
void SetSpriteOrigin(sfSprite** _sprite, sfVector2f divide);
#endif
