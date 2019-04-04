#include "menu.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


Menu::Menu() {}

Menu::Menu(SDL_Rect *menuitems)
{
	start_game = { 800, 20, 150, 70 };
	scoreboard = { 800, 110, 150, 70 };
	options = { 800, 200, 150, 70 };
	quit = { 800, 290, 150, 70 };

	menuitems[0] = start_game;
	menuitems[1] = scoreboard;
	menuitems[2] = options;
	menuitems[3] = quit;

	this->start_game_textura = nullptr;
	this->scoreboard_textura = nullptr;
	this->options_textura = nullptr;
	this->quit_textura = nullptr;
}


Menu::~Menu()
{
	SDL_DestroyTexture(start_game_textura);
	SDL_DestroyTexture(scoreboard_textura);
	SDL_DestroyTexture(options_textura);
	SDL_DestroyTexture(quit_textura);
}

void Menu::render_menu(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, start_game_textura, NULL, &start_game);
	SDL_RenderCopy(renderer, scoreboard_textura, NULL, &scoreboard);
	SDL_RenderCopy(renderer, options_textura, NULL, &options);
	SDL_RenderCopy(renderer, quit_textura, NULL, &quit);
}

void Menu::init(SDL_Surface *povrsina, TTF_Font *font, SDL_Color &boja, SDL_Renderer *renderer)
{
	povrsina = TTF_RenderText_Solid(font, "Start game", boja);
	start_game_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
	povrsina = TTF_RenderText_Solid(font, "Scoreboard", boja);
	scoreboard_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
	povrsina = TTF_RenderText_Solid(font, "Options", boja);
	options_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
	povrsina = TTF_RenderText_Solid(font, "Quit", boja);
	quit_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
}
