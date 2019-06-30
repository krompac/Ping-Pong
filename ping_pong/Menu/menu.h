#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Menu
{
	private:
		SDL_Rect start_game;
		SDL_Rect scoreboard;
		SDL_Rect options;
		SDL_Rect quit;

		SDL_Texture *start_game_texture;
		SDL_Texture *scoreboard_texture;
		SDL_Texture *options_texture;
		SDL_Texture *quit_texture;

	public:
		Menu();
		Menu(SDL_Rect *menuitems);
		~Menu();

		void Render_Menu(SDL_Renderer *renderer);
		void Init(SDL_Surface *surface, TTF_Font *font, SDL_Color &color, SDL_Renderer *renderer);
};

