#include "Options.h"

SpeedOptions::SpeedOptions() {}

SpeedOptions::SpeedOptions(float &speed) : Options("Ball speed", 30, 60)
{
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

bool SpeedOptions::Update_Options(SDL_Renderer **renderer, int change_index)
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

		Set_Texture(&option_text, renderer, Get_Option(), TTF_OpenFont("images/Sans.ttf", 100));

		return true;
	}
}

std::string SpeedOptions::Get_Option()
{
	return possible_speed[array_index];
}