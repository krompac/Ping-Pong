#include "ChangeTextureColor.h"

void Change_Texture_Color(SDL_Texture **texture, Colors color)
{
	switch (color)
	{
		case Blue:
			SDL_SetTextureColorMod(*texture, 0x00, 0x00, 0xff);
			break;
		case Red:
			SDL_SetTextureColorMod(*texture, 0xff, 0x00, 0x00);
			break;
		case Green:
			SDL_SetTextureColorMod(*texture, 0x00, 0xff, 0x00);
			break;
		case White:
			SDL_SetTextureColorMod(*texture, 0xff, 0xff, 0xff);
			break;
		case Yellow:
			SDL_SetTextureColorMod(*texture, 0xff, 0xff, 0x00);
			break;
		case Cyan:
			SDL_SetTextureColorMod(*texture, 0x00, 0xff, 0xff);
			break;
		case Magenta:
			SDL_SetTextureColorMod(*texture, 0xff, 0x00, 0xff);
			break;
		default:
			break;
	}
}

//Change SDL_Rect color
void Fill_Rect_With_Color(SDL_Renderer *renderer, SDL_Rect &rect_to_fill, Colors color)
{
	switch (color)
	{
		case Blue:
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
			break;
		case Red:
			SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
			break;
		case Green:
			SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
			break;
		case White:
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
			break;
		case Yellow:
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
			break;
		case Cyan:
			SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0xff);
			break;
		case Magenta:
			SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
			break;
	}

	SDL_RenderFillRect(renderer, &rect_to_fill);
}