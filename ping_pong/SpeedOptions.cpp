#include "Options.h"

SpeedOptions::SpeedOptions() {}

SpeedOptions::SpeedOptions(float &speed) : Options()
{
	this->ball_speed_text = nullptr;
	this->ball_speed_text_label = nullptr;
	this->left_arrow_head_texture = nullptr;
	this->right_arrow_head_texture = nullptr;

	ball_speed_label = { 30, 30, 160, 50 };

	int x = ball_speed_label.x;
	int y = ball_speed_label.y;
	int w = ball_speed_label.w;

	left_arrow = { x + w + 10, 40, 40, 35 };
	ball_speed_rect = { x + w + 60, 35, 120, 45 };
	right_arrow = { x + w + ball_speed_rect.w + 70, 40, 40, 35 };

	possible_speed = new std::string[3];

	possible_speed[0] = "  Slow  ";
	possible_speed[1] = " Normal ";
	possible_speed[2] = "  Fast  ";

	array_index = 1;
	ball_speed = &speed;
	*ball_speed = 5;
}

SpeedOptions::~SpeedOptions()
{
	//delete possible_speed;
}

bool SpeedOptions::UpdateOptions(SDL_Renderer **renderer, int change_index)
{
	int possible_index = array_index;

	if (change_index > 0 && array_index != 2)
	{
		array_index++;
	}
	else if (change_index < 0 && array_index != 0)
	{
		array_index--;
	}

	if (possible_index == array_index)
	{
		return false;
	}
	else
	{
		switch (array_index)
		{
			case 0:
				*ball_speed = 3;
				break;
			case 1:
				*ball_speed = 5;
				break;
			case 2:
				*ball_speed = 7;
				break;
		}
		SetTexture(&ball_speed_text, renderer, GetOption(), TTF_OpenFont("images/Sans.ttf", 100));

		return true;
	}
}

std::string SpeedOptions::GetOption()
{
	return possible_speed[array_index];
}

void SpeedOptions::Init_Textures(SDL_Renderer **renderer, TTF_Font * font)
{
	SetTexture(&left_arrow_head_texture, renderer, "images/left_arrow_head.png");
	SetTexture(&right_arrow_head_texture, renderer, "images/right_arrow_head.png");

	SetTexture(&ball_speed_text, renderer, GetOption(), font);
	SetTexture(&ball_speed_text_label, renderer, "Ball speed:", font);
}

void SpeedOptions::Render(SDL_Renderer ** renderer)
{
	SDL_RenderDrawRect(*renderer, &ball_speed_rect);

	SDL_RenderCopy(*renderer, ball_speed_text_label, NULL, &ball_speed_label);
	SDL_RenderCopy(*renderer, ball_speed_text, NULL, &ball_speed_rect);
	SDL_RenderCopy(*renderer, left_arrow_head_texture, NULL, &left_arrow);
	SDL_RenderCopy(*renderer, right_arrow_head_texture, NULL, &right_arrow);
}

void SpeedOptions::FreeData()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(ball_speed_text);
	SDL_DestroyTexture(ball_speed_text_label);
	SDL_DestroyTexture(left_arrow_head_texture);
	SDL_DestroyTexture(right_arrow_head_texture);
}