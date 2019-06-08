#pragma once
#include <vector>
#include "Window.h"

class UI_Element
{
	public:
		UI_Element();
		UI_Element(int x, int y, int w, int h);
		
		void Render(SDL_Renderer **renderer, bool draw_rect = false);

		SDL_Rect rect;
		SDL_Texture *texture;
		std::string text;
};

struct Score_Entry
{
	std::string player1_name;
	int player1_score;

	std::string player2_name;
	int player2_score;
};

class Scoreboard : public Window
{
	public:
		Scoreboard();
		Scoreboard(Menu &menu);
		~Scoreboard();

		bool Window_Action(SDL_Renderer **renderer, bool is_message = false);
		void Render(SDL_Renderer **renderer);
		void Init_Texture(SDL_Renderer **renderer, TTF_Font *font);
		void Free_Data();
		void Add_Score_Entry(Score_Entry entry);

	private:
		void Set_Texture(SDL_Texture **texture, SDL_Renderer **renderer, std::string text, TTF_Font *font);

		SDL_Surface *surface;
		SDL_Color color;

		std::vector<Score_Entry> score_entrys;

		UI_Element title;
		UI_Element player1_entry;
		UI_Element player1_score;
		UI_Element colon;
		UI_Element player2_entry;
		UI_Element player2_score;

		std::string title_text;
};
