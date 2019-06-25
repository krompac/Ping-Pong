#include "Scoreboard.h"

UI_Element::UI_Element()
{
	texture = nullptr;
}

void UI_Element::Render(SDL_Renderer ** renderer, bool draw_rect)
{
	if (draw_rect)
	{
		SDL_RenderDrawRect(*renderer, &rect);
	}

	SDL_RenderCopy(*renderer, this->texture, NULL, &rect);
}

void UI_Element::Set_Texture(SDL_Renderer ** renderer, TTF_Font * font, SDL_Surface * surface, SDL_Color & color)
{
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	this->texture = SDL_CreateTextureFromSurface(*renderer, surface);
}

void UI_Element::Free_Data()
{
	SDL_DestroyTexture(texture);
}