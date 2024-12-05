#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/System.h"
#include "SFML/Graphics.h"

sfBool CollisionRectRect(sfIntRect* const, sfIntRect* const);

sfBool CollisionPointRect(sfFloatRect _rect1, sfVector2i const _point);

#endif

