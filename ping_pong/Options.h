#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


class Options
{
	public:
		virtual bool UpdateOptions(int change_index = 0) = 0;
		virtual std::string GetOption() = 0;
};

class SpeedOptions : public Options
{
	private:
		std::string *possible_speed;
		int array_index;
		int ball_speed;
	
	public:
		SpeedOptions();
		~SpeedOptions();
	
		bool UpdateOptions(int change_index = 0);
		std::string GetOption();
		int GetBallSpeed();
};