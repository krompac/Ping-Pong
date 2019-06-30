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

	this->start_game_texture = nullptr;
	this->scoreboard_texture = nullptr;
	this->options_texture = nullptr;
	this->quit_texture = nullptr;
}


Menu::~Menu()
{
	SDL_DestroyTexture(start_game_texture);
	SDL_DestroyTexture(scoreboard_texture);
	SDL_DestroyTexture(options_texture);
	SDL_DestroyTexture(quit_texture);
}

void Menu::Render_Menu(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, start_game_texture, NULL, &start_game);
	SDL_RenderCopy(renderer, scoreboard_texture, NULL, &scoreboard);
	SDL_RenderCopy(renderer, options_texture, NULL, &options);
	SDL_RenderCopy(renderer, quit_texture, NULL, &quit);
}

void Menu::Init(SDL_Surface *surface, TTF_Font *font, SDL_Color &color, SDL_Renderer *renderer)
{
	surface = TTF_RenderText_Solid(font, "Start game", color);
	start_game_texture = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderText_Solid(font, "Scoreboard", color);
	scoreboard_texture = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderText_Solid(font, "Options", color);
	options_texture = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderText_Solid(font, "Quit", color);
	quit_texture = SDL_CreateTextureFromSurface(renderer, surface);
}