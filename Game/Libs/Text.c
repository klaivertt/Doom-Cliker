#include "Text.h"

TextManager text = { 0 };

void LoadTextManager(void)
{
    text.font = sfFont_createFromFile("Assets/Fonts/font.ttf");
}
sfText* InitText(sfText* _text, const char* _string, unsigned int _fontSize, sfVector2f _position) 
{
    // Création du texte
    _text = sfText_create();
    sfText_setFont(_text, text.font);
    sfText_setCharacterSize(_text, _fontSize);
    sfText_setPosition(_text, _position);

    char string[30];
    sprintf_s(string, sizeof(string), _string);
    sfText_setString(_text, string);

    return _text;
}

void UpdateText(sfText* _text, const char* _string, int _value)
{
    char string[30];
    sprintf_s(string, sizeof(string), _string , _value);
    sfText_setString(_text, string);
}
