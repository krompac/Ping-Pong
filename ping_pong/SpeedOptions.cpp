#include "Options.h"

SpeedOptions::SpeedOptions() {}

SpeedOptions::SpeedOptions(float &speed) : Options()
{
	option_label = { 30, 30, 160, 50 };

	int x = option_label.x;
	int y = option_label.y;
	int w = option_label.w;

	left_arrow = { x + w + 10, 40, 40, 35 };
	option_rect = { x + w + 60, 35, 120, 45 };
	right_arrow = { x + w + option_rect.w + 70, 40, 40, 35 };

	possible_speed = new std::string[3];

	possible_speed[0] = "  Slow  ";
	possible_speed[1] = " Normal ";
	possible_speed[2] = "  Fast  ";

	array_index = 1;
	ball_speed = &speed;
	*ball_speed = 5;

	active = true;
	option_label_string = "Ball speed";
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

		SetTexture(&option_text, renderer, GetOption(), TTF_OpenFont("images/Sans.ttf", 100));

		return true;
	}
}

std::string SpeedOptions::GetOption()
{
	return possible_speed[array_index];
}