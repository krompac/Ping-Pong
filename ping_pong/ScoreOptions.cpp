#include "Options.h"

ScoreOptions::ScoreOptions() {}

ScoreOptions::ScoreOptions(int &max_score) : Options()
{
	this->max_score = &max_score;

	this->left_arrow_head_texture = nullptr;
	this->right_arrow_head_texture = nullptr;
	this->max_score_label_text = nullptr;
	this->max_score_text = nullptr;

	max_score_label = { 30, 110, 160, 50 };

	int x = max_score_label.x;
	int y = max_score_label.y;
	int w = max_score_label.w;

	left_arrow = { x + w + 10, y + 10, 40, 35 };
	max_score_text_rect = { x + w + 60, y + 5, 60, 45 };
	right_arrow = { x + w + max_score_text_rect.w + 70, y + 10, 40, 35 };

	possible_score = std::to_string(max_score);
}

ScoreOptions::~ScoreOptions()
{
}

bool ScoreOptions::UpdateOptions(SDL_Renderer ** renderer, int change_index)
{
	return false;
}

std::string ScoreOptions::GetOption()
{
	return possible_score;
}

void ScoreOptions::Init_Textures(SDL_Renderer ** renderer, TTF_Font * font)
{
	SetTexture(&left_arrow_head_texture, renderer, "images/left_arrow_head.png");
	SetTexture(&right_arrow_head_texture, renderer, "images/right_arrow_head.png");

	SetTexture(&max_score_text, renderer, GetOption(), font);
	SetTexture(&max_score_label_text, renderer, "Max score:", font);
}

void ScoreOptions::FreeData()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(max_score_text);
	SDL_DestroyTexture(max_score_label_text);
	SDL_DestroyTexture(left_arrow_head_texture);
	SDL_DestroyTexture(right_arrow_head_texture);
}

void ScoreOptions::Render(SDL_Renderer ** renderer)
{
	SDL_RenderDrawRect(*renderer, &max_score_text_rect);

	SDL_RenderCopy(*renderer, max_score_label_text, NULL, &max_score_label);
	SDL_RenderCopy(*renderer, max_score_text, NULL, &max_score_text_rect);
	SDL_RenderCopy(*renderer, left_arrow_head_texture, NULL, &left_arrow);
	SDL_RenderCopy(*renderer, right_arrow_head_texture, NULL, &right_arrow);
}
