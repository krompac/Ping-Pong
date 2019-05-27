#include "Options.h"

ScoreOptions::ScoreOptions() {}

ScoreOptions::ScoreOptions(int &max_score) : Options()
{
	this->max_score = &max_score;

	option_label = { 30, 110, 160, 50 };

	int x = option_label.x;
	int y = option_label.y;
	int w = option_label.w;

	left_arrow = { x + w + 10, y + 10, 40, 35 };
	option_rect = { x + w + 60, y + 5, 60, 45 };
	right_arrow = { x + w + option_rect.w + 70, y + 10, 40, 35 };

	possible_score = std::to_string(max_score);

	active = false;
	option_label_string = "Max score";
}

ScoreOptions::~ScoreOptions()
{
}

bool ScoreOptions::UpdateOptions(SDL_Renderer ** renderer, int change_index)
{
	int possible_index = *max_score + change_index;

	if (possible_index >= 5 && possible_index <= 20)
	{
		*max_score = possible_index;
		possible_score = std::to_string(possible_index);
		SetTexture(&option_text, renderer, GetOption(), TTF_OpenFont("images/Sans.ttf", 100));

		return true;
	}

	return false;
}

std::string ScoreOptions::GetOption()
{
	return possible_score;
}