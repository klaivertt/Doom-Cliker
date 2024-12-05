#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <SFML/Graphics.h>

typedef struct Animation
{
	sfTexture* texture;
	sfSprite* sprite;
	sfIntRect size;
	int frameCount;
	int frameRate;
	int currentFrame;
	float timer;
	sfVector2f start;
	sfBool isLooping;
	sfBool isFinished;
}Animation;

void CreateAnimation(Animation* _anim, char* const _filepath, int _maxFrame, int _frameCount, int _frameRate, sfBool _isLooping, sfVector2f _start);
void UpdateAnimation(Animation*, float);
void ResetAnimation(Animation*);

#endif