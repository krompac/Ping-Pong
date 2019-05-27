#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "Window.h"
#include "menu.h"
#include "Options.h"
#undef main

class Settings : public Window
{
	private:
		SDL_Event event_handler;

		Menu *menu;
		std::vector<Options *> options;
		int options_position;
		int number_of_options;

	public:
		Settings();
		Settings(Menu &menu, SpeedOptions &speed_options, ScoreOptions &score_options);
		~Settings();

		void Render(SDL_Renderer **renderer);
		void FreeData();
		bool Window_Action(SDL_Renderer **renderer, bool is_message = false);
		void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);
};

