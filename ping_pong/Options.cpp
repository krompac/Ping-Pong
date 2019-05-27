#include "Options.h"

Options::Options()
{
	this->surface = nullptr;
	this->left_arrow_head_texture = nullptr;
	this->right_arrow_head_texture = nullptr;
	this->option_text = nullptr;
	this->option_text_label = nullptr;

	color = { 255, 255, 255 };
}

void Options::SetTexture(SDL_Texture **texture, SDL_Renderer **renderer, std::string text, TTF_Font *font)
{
	if (font == nullptr)
	{
		surface = IMG_Load(text.c_str());
		*texture = SDL_CreateTextureFromSurface(*renderer, surface);
		SDL_SetTextureColorMod(*texture, 0xff, 0x00, 0x00);
	}
	else
	{
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
		*texture = SDL_CreateTextureFromSurface(*renderer, surface);
	}
}

void Options::Init_Textures(SDL_Renderer ** renderer, TTF_Font * font)
{
	SetTexture(&left_arrow_head_texture, renderer, "images/left_arrow_head.png");
	SetTexture(&right_arrow_head_texture, renderer, "images/right_arrow_head.png");

	SetTexture(&option_text, renderer, GetOption(), font);
	SetTexture(&option_text_label, renderer, option_label_string.c_str(), font);
}

void Options::SetActive(bool active)
{
	this->active = active;
}

void Options::FreeData()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(option_text);
	SDL_DestroyTexture(option_text_label);
	SDL_DestroyTexture(left_arrow_head_texture);
	SDL_DestroyTexture(right_arrow_head_texture);
}

void Options::Render(SDL_Renderer ** renderer)
{
	if (active)
	{
		SDL_RenderDrawRect(*renderer, &option_rect);
	}

	SDL_RenderCopy(*renderer, option_text_label, NULL, &option_label);
	SDL_RenderCopy(*renderer, option_text, NULL, &option_rect);
	SDL_RenderCopy(*renderer, left_arrow_head_texture, NULL, &left_arrow);
	SDL_RenderCopy(*renderer, right_arrow_head_texture, NULL, &right_arrow);
}