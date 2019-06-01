#include "Scoreboard.h"

Scoreboard::Scoreboard() {}

Scoreboard::Scoreboard(Menu &menu) : Window(menu)
{

}

Scoreboard::~Scoreboard(){}

bool Scoreboard::Window_Action(SDL_Renderer **renderer, bool is_message)
{
	while (SDL_PollEvent(&event_handler))
	{
		if (event_handler.key.keysym.sym == SDLK_ESCAPE || event_handler.type == SDL_QUIT)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return true;
}

void Scoreboard::Render(SDL_Renderer ** renderer)
{
	Window::Render(renderer);


	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderPresent(*renderer);
}
