#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#pragma once
class Window
{
	public:
		virtual bool Window_Action(SDL_Renderer *renderer, bool is_message = false) = 0;

	protected:
		SDL_Rect render_window;
};

