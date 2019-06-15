#pragma once
#include "Window.h"

class Scoreboard : public Window
{
	public:
		Scoreboard();
		Scoreboard(Menu &menu);
		~Scoreboard();

		bool Window_Action(SDL_Renderer **renderer, bool is_message = false);
		void Render(SDL_Renderer **renderer);

	private:

};

