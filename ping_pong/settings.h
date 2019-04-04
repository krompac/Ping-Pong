#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "game.h"
#undef main

class settings : Game
{
public:
	settings();
	~settings();
};

