#include "settings.h"

Settings::Settings() {}

Settings::Settings(Menu &menu, SpeedOptions &speed_options, ScoreOptions &score_options,
	TextureColorOptions &ball_color_options, PadColorOptions &left_pad, PadColorOptions &right_pad) : Window(menu) //, ColorOptions &left_pad_color_options, ColorOptions &right_pad_color_options)
{
	options_position = 0;
	number_of_options = 1;
	this->options.push_back(&speed_options);
	this->options.push_back(&score_options);
	this->options.push_back(&ball_color_options);
	this->options.push_back(&left_pad);
	this->options.push_back(&right_pad);
}

Settings::~Settings()
{
	//delete options;
}

void Settings::Render(SDL_Renderer **renderer)
{
	Window::Render(renderer);

	for (auto option : options)
	{
		option->Render(renderer);
	}

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(*renderer);
	SDL_Delay(1);
}

void Settings::FreeData()
{
	for (auto option : options)
	{
		option->Free_Data();
	}
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
					options[options_position]->Update_Options(renderer, -1);
					break;
				case SDLK_RIGHT:
					options[options_position]->Update_Options(renderer, 1);
					break;
				case SDLK_UP:
					if (options_position > 0)
					{
						options[options_position]->SetActive(false);
						options_position--;
						options[options_position]->SetActive(true);
					}
					break;
				case SDLK_DOWN:
					if (options_position < options.size() - 1)
					{
						options[options_position]->SetActive(false);
						options_position++;
						options[options_position]->SetActive(true);
					}
					break;
			}
		}
	}

	return true;
}

void Settings::Init_Textures(SDL_Renderer **renderer, TTF_Font *font)
{
	for (auto option : options)
	{
		option->Init_Textures(renderer, font);
	}
}