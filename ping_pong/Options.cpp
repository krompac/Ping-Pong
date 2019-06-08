#include "Options.h"

Options::Options(){}

Options::Options(std::string option_label_string, int options_y_position, int extended_option_width)
{
	this->surface = nullptr;
	this->left_arrow_head_texture = nullptr;
	this->right_arrow_head_texture = nullptr;
	this->option_text = nullptr;
	this->option_text_label = nullptr;

	color = { 255, 255, 255 };
	active = false;

	option_label = { 30, options_y_position, 160, 50 };

	int x = option_label.x;
	int y = option_label.y;
	int w = option_label.w;

	left_arrow = { x + w + 10, y + 10, 40, 35 };
	option_rect = { x + w + 60, y + 5, 60 + extended_option_width, 45 };
	right_arrow = { x + w + option_rect.w + 70, y + 10, 40, 35 };

	this->option_label_string = option_label_string;
}

void Options::Set_Texture(SDL_Texture **texture, SDL_Renderer **renderer, std::string text, TTF_Font *font)
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
	Set_Texture(&left_arrow_head_texture, renderer, "images/left_arrow_head.png");
	Set_Texture(&right_arrow_head_texture, renderer, "images/right_arrow_head.png");

	Set_Texture(&option_text, renderer, Get_Option(), font);
	Set_Texture(&option_text_label, renderer, option_label_string.c_str(), font);
}

void Options::Set_Active(bool active)
{
	this->active = active;
}

void Options::Free_Data()
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