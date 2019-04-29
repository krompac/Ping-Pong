#include "Options.h"

SpeedOptions::SpeedOptions() {}

SpeedOptions::SpeedOptions(float &speed)
{
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

bool SpeedOptions::UpdateOptions(int change_index)
{
	if (change_index > 0 && array_index != 2)
	{
		array_index++;
		*ball_speed += 2;
		return true;
	}
	else if (change_index < 0 && array_index != 0)
	{
		array_index--;
		*ball_speed -= 2;
		return true;
	}

	return false;
}

std::string SpeedOptions::GetOption()
{
	return possible_speed[array_index];
}
