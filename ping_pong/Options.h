#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Options
{
	public:
		Options();
		void SetTexture(SDL_Texture **texture, SDL_Renderer **renderer, std::string text, TTF_Font *font = nullptr);

		virtual bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0) = 0;
		virtual std::string GetOption() = 0;
		virtual void Init_Textures(SDL_Renderer **renderer, TTF_Font *font) = 0;
		virtual void FreeData() = 0;
		virtual void Render(SDL_Renderer **renderer) = 0;

	protected:
		SDL_Surface *surface;
		SDL_Color color;
};

class SpeedOptions : public Options
{
	private:
		std::string *possible_speed;
		int array_index;
		float *ball_speed;

		SDL_Texture *ball_speed_text;
		SDL_Texture *ball_speed_text_label;
		SDL_Texture *left_arrow_head_texture;
		SDL_Texture *right_arrow_head_texture;

		SDL_Rect ball_speed_rect;
		SDL_Rect ball_speed_label;
		SDL_Rect left_arrow;
		SDL_Rect right_arrow;
	
	public:
		SpeedOptions();
		SpeedOptions(float &speed);
		~SpeedOptions();
	
		bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0);
		std::string GetOption();
		void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);
		void Render(SDL_Renderer **renderer);
		void FreeData();
};