#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ColorEnum.h"

//Change Texture Color
void Change_Texture_Color(SDL_Texture **texture, Colors color);

//Change SDL_Rect color
void Fill_Rect_With_Color(SDL_Renderer *renderer, SDL_Rect &rect_to_fill, Colors color);