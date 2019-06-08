#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "ColorEnum.h"

class Options
{
	public:
		Options();
		Options(std::string option_label_string, int options_y_position, int extended_option_width = 0);
		void Set_Texture(SDL_Texture **texture, SDL_Renderer **renderer, std::string text, TTF_Font *font = nullptr);
		void Set_Active(bool active);

		virtual void Free_Data();
		virtual void Render(SDL_Renderer **renderer);
		virtual void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);

		virtual bool Update_Options(SDL_Renderer **renderer, int change_index = 0) = 0;
		virtual std::string Get_Option() = 0;

	protected:
		std::string option_label_string;

		SDL_Texture *left_arrow_head_texture;
		SDL_Texture *right_arrow_head_texture;
		SDL_Texture *option_text;
		SDL_Texture *option_text_label;

		SDL_Rect left_arrow;
		SDL_Rect right_arrow;
		SDL_Rect option_label;

		SDL_Surface *surface;
		SDL_Color color;
		SDL_Rect option_rect;

		bool active;
};

class SpeedOptions : public Options
{
	private:
		std::string *possible_speed;
		int array_index;
		float *ball_speed;
	
	public:
		SpeedOptions();
		SpeedOptions(float &speed);
		~SpeedOptions();
	
		bool Update_Options(SDL_Renderer **renderer, int change_index = 0);
		std::string Get_Option();
};

class ScoreOptions : public Options
{
	private:
		std::string possible_score;
		int *max_score;

	public:
		ScoreOptions();
		ScoreOptions(int &max_score);
		~ScoreOptions();

		bool Update_Options(SDL_Renderer **renderer, int change_index = 0);
		std::string Get_Option();
};

class TextureColorOptions : public Options
{
	private:
		SDL_Texture **texture_to_change;
		Colors active_color;

	public:
		TextureColorOptions();
		//190 za ball color, 270 za left pad color, 350 za left pad color
		TextureColorOptions(SDL_Texture **texture, std::string option_label_string, int options_y_position, Colors start_color);
		~TextureColorOptions();

		bool Update_Options(SDL_Renderer **renderer, int change_index = 0);
		std::string Get_Option();
		void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);
};

class PadColorOptions : public Options
{
	private:
		Colors *active_color;
		std::string pad_text;

	public:
		PadColorOptions();
		PadColorOptions(std::string option_label_string, int options_y_position, Colors &color, bool left_pad = false);
		~PadColorOptions();

		bool Update_Options(SDL_Renderer **renderer, int change_index = 0);
		std::string Get_Option();
		void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);
};