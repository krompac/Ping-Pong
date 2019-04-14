#include "settings.h"

Settings::Settings() {}

Settings::Settings(Menu &menu, SpeedOptions &speed_options)
{
	this->options = &speed_options;
	//this->options = new SpeedOptions();
	this->menu = &menu;
	this->surface = nullptr;
	render_window = { 20, 20, 720, 560 };
	ball_speed_label = { 30, 30, 160, 50 };

	int x = ball_speed_label.x;
	int y = ball_speed_label.y;
	int w = ball_speed_label.w;

	left_arrow = { x + w + 10, 40, 40, 35 };
	ball_speed = { x + w + 60, 35, 120, 45 };
	right_arrow = { x + w + ball_speed.w + 70, 40, 40, 35 };

	this->ball_speed_text = nullptr;
	this->ball_speed_text_label = nullptr;
	this->left_arrow_head_texture = nullptr;
	this->right_arrow_head_texture = nullptr;

	color = { 255, 255, 255 };
}

Settings::~Settings()
{
	//delete options;

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(ball_speed_text);
	SDL_DestroyTexture(ball_speed_text_label);
	SDL_DestroyTexture(left_arrow_head_texture);
	SDL_DestroyTexture(right_arrow_head_texture);
}

void Settings::Render(SDL_Renderer *renderer)
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &render_window);
	SDL_RenderDrawRect(renderer, &ball_speed);

	this->menu->Render_Menu(renderer);

	SDL_RenderCopy(renderer, ball_speed_text_label, NULL, &ball_speed_label);
	SDL_RenderCopy(renderer, ball_speed_text, NULL, &ball_speed);
	SDL_RenderCopy(renderer, left_arrow_head_texture, NULL, &left_arrow);
	SDL_RenderCopy(renderer, right_arrow_head_texture, NULL, &right_arrow);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(renderer);
}

bool Settings::Window_Action(SDL_Renderer *renderer, bool is_message)
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
					if (this->options->UpdateOptions(-1))
					{
						SetTexture(&ball_speed_text, renderer, this->options->GetOption(), TTF_OpenFont("images/Sans.ttf", 100));
					}
					break;
				case SDLK_RIGHT:
					if (this->options->UpdateOptions(1))
					{
						SetTexture(&ball_speed_text, renderer, this->options->GetOption(), TTF_OpenFont("images/Sans.ttf", 100));
					}
					break;
			}
		}
	}

	return true;
}

void Settings::Init_Textures(SDL_Renderer *renderer, TTF_Font *font)
{
	SetTexture(&left_arrow_head_texture, renderer, "images/left_arrow_head.png");
	SetTexture(&right_arrow_head_texture, renderer, "images/right_arrow_head.png");

	SetTexture(&ball_speed_text, renderer, this->options->GetOption(), font);
	SetTexture(&ball_speed_text_label, renderer, "Ball speed:", font);
}

void Settings::SetTexture(SDL_Texture **texture, SDL_Renderer *renderer, std::string text, TTF_Font *font)
{
	if (font == nullptr)
	{
		surface = IMG_Load(text.c_str());
		*texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_SetTextureColorMod(*texture, 0xff, 0x00, 0x00);
	}
	else
	{
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
		*texture = SDL_CreateTextureFromSurface(renderer, surface);
	}
}