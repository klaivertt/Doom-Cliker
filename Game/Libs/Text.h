#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <SFML/Graphics.h>

// Structure pour gérer un texte CSFML
typedef struct {
    sfFont* font;
} TextManager;

void LoadTextManager(void);

void InitText(sfText** _text, const char* _string, unsigned int _fontSize, sfVector2f _position);

void UpdateText(sfText** _text, const char* _string, int _value);
#endif
