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
		void SetActive(bool active);

		virtual void FreeData();
		virtual void Render(SDL_Renderer **renderer);
		virtual void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);

		virtual bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0) = 0;
		virtual std::string GetOption() = 0;

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
	
		bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0);
		std::string GetOption();
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

		bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0);
		std::string GetOption();
};

//class ColorOptions : public Options
//{
//protected:
//	SDL_Texture **texture_to_change;
//
//
//
//public:
//	bool UpdateOptions(SDL_Renderer **renderer, int change_index = 0);
//	std::string GetOption();
//	void Init_Textures(SDL_Renderer **renderer, TTF_Font *font);
//	void FreeData();
//	void Render(SDL_Renderer **renderer);
//};
