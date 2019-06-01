#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "menu.h"

#pragma once
class Window
{
	public:
		Window();
		Window(Menu &menu);
		virtual void Render(SDL_Renderer **renderer);
		virtual bool Window_Action(SDL_Renderer **renderer, bool is_message = false) = 0;

	protected:
		SDL_Rect render_window;
		SDL_Event event_handler;

		Menu *menu;
};

