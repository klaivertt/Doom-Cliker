#include "../Game/Libs/Collision.h"
#include "../Game/Libs/Common.h"

sfBool CollisionRectRect(sfIntRect* const _rect1, sfIntRect* const _rect2)
{
	if (sfIntRect_intersects(_rect1, _rect2, NULL))
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
    
}

sfBool CollisionPointRect(sfFloatRect _rect1, sfVector2i const _point)
{
    if (sfFloatRect_contains(&_rect1, (float)_point.x, (float)_point.y))
    {
        return sfTrue;
    }
    else
    {
        return sfFalse;
    }
}