#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Window.h"
#include "menu.h"
#include "Options.h"
#undef main

class Settings : public Window
{
	private:
		SDL_Surface *surface;
		SDL_Event event_handler;

		SDL_Texture *ball_speed_text;
		SDL_Texture *ball_speed_text_label;
		SDL_Texture *left_arrow_head_texture;
		SDL_Texture *right_arrow_head_texture;

		SDL_Rect ball_speed;
		SDL_Rect ball_speed_label;
		SDL_Rect left_arrow;
		SDL_Rect right_arrow;

		SDL_Color color;

		Menu *menu;
		Options *options;

		void SetTexture(SDL_Texture **texture, SDL_Renderer *renderer, std::string text, TTF_Font *font = nullptr);

	public:
		Settings();
		Settings(Menu &menu, SpeedOptions &speed_options);
		~Settings();

		void Render(SDL_Renderer *renderer);
		bool Window_Action(SDL_Renderer *renderer, bool is_message = false);
		void Init_Textures(SDL_Renderer *renderer, TTF_Font *font);
};

