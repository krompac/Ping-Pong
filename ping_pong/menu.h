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

		SDL_Texture *start_game_textura;
		SDL_Texture *scoreboard_textura;
		SDL_Texture *options_textura;
		SDL_Texture *quit_textura;

	public:
		Menu();
		Menu(SDL_Rect *menuitems);
		~Menu();

		void render_menu(SDL_Renderer *renderer);
		void init(SDL_Surface *povrsina, TTF_Font *font, SDL_Color &boja, SDL_Renderer *renderer);
};

