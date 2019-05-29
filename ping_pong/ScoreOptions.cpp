#include "Options.h"

ScoreOptions::ScoreOptions() {}

ScoreOptions::ScoreOptions(int &max_score) : Options("Max score", 110)
{
	this->max_score = &max_score;

	possible_score = std::to_string(max_score);
}

ScoreOptions::~ScoreOptions()
{
}

bool ScoreOptions::Update_Options(SDL_Renderer ** renderer, int change_index)
{
	int possible_index = *max_score + change_index;

	if (possible_index >= 5 && possible_index <= 20)
	{
		*max_score = possible_index;
		possible_score = std::to_string(possible_index);
		SetTexture(&option_text, renderer, Get_Option(), TTF_OpenFont("images/Sans.ttf", 100));

		return true;
	}

	return false;
}

std::string ScoreOptions::Get_Option()
{
	return possible_score;
}