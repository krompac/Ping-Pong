#include "Options.h"

Options::Options()
{
	this->surface = nullptr;
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