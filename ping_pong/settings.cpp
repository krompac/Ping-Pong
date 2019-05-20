#include "settings.h"

Settings::Settings() {}

Settings::Settings(Menu &menu, SpeedOptions &speed_options, ScoreOptions &score_options)
{
	this->options = &speed_options;
	this->options2 = &score_options;
	this->menu = &menu;
	render_window = { 20, 20, 720, 560 };
}

Settings::~Settings()
{
	//delete options;
}

void Settings::Render(SDL_Renderer **renderer)
{
	SDL_RenderClear(*renderer);

	SDL_SetRenderDrawColor(*renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(*renderer, &render_window);
	this->options->Render(renderer);
	this->options2->Render(renderer);

	this->menu->Render_Menu(*renderer);

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(*renderer);
	SDL_Delay(1);
}

void Settings::FreeData()
{
	this->options->FreeData();
	this->options2->FreeData();
}

bool Settings::Window_Action(SDL_Renderer **renderer, bool is_message)
{
	while (SDL_PollEvent(&event_handler))
	{
		if (event_handler.key.keysym.sym == SDLK_ESCAPE || event_handler.type == SDL_QUIT)
		{
			return false;
		}

		if (event_handler.type == SDL_KEYDOWN)
		{
			switch (event_handler.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					return false;
				case SDLK_LEFT:
					this->options->UpdateOptions(renderer, -1);
					break;
				case SDLK_RIGHT:
					this->options->UpdateOptions(renderer, 1);
					break;
			}
		}
	}

	return true;
}

void Settings::Init_Textures(SDL_Renderer **renderer, TTF_Font *font)
{
	this->options->Init_Textures(renderer, font);
	this->options2->Init_Textures(renderer, font);
}